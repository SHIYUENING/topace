#include "Video.h"

CVideo::CVideo(void)
:isend(0)
{
}

CVideo::~CVideo(void)
{
}
void CVideo::InitVideo(unsigned int VideoTexSize)
{

	unsigned int* data;						// �洢����

	// Ϊ�������ݣ�wh*wh*4�������洢��
	data = (unsigned int*)new GLuint[((VideoTexSize * VideoTexSize)* 3 * sizeof(unsigned int))];
	ZeroMemory(data,((VideoTexSize * VideoTexSize)* 3 * sizeof(unsigned int)));	// ����洢��

	glGenTextures(1, &VideoTexID);				// ����һ������
	glBindTexture(GL_TEXTURE_2D, VideoTexID);			// ��������
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, VideoTexSize, VideoTexSize, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	

	delete [] data;						// �ͷ�����
	
	av_register_all();
}
bool CVideo::LoadVideo(const char *filename)
{
	if(av_open_input_file(&pFormatCtx, filename, NULL, 0, NULL)!=0)
	{
		MessageBox(NULL,"cant open.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		return false;
	}

	if(av_find_stream_info(pFormatCtx)<0)
	{
		MessageBox(NULL,"cant read.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		return false;
	}

	videoStream=-1;
	for(int i=0; i<pFormatCtx->nb_streams; i++)
		if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO)
		{
			videoStream=i;
			break;
		}
	if(videoStream==-1)
	{
		MessageBox(NULL,"cant videoStream.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		return false;
	}

	pCodecCtx=pFormatCtx->streams[videoStream]->codec;

	AVCodec *pCodec;


	pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
	if(pCodec==NULL)
	{
		MessageBox(NULL,"cant pCodec==NULL.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		return false;
	}

	if(pCodec->capabilities & CODEC_CAP_TRUNCATED)
		pCodecCtx->flags|=CODEC_FLAG_TRUNCATED;

// �򿪽�����
	if(avcodec_open(pCodecCtx, pCodec)<0)
	{
		MessageBox(NULL,"cant avcodec_open.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		return false;
	}





	pFrame=avcodec_alloc_frame();

	pFrameRGB=avcodec_alloc_frame();

	int     numBytes;
	uint8_t *buffer;

	numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
    pCodecCtx->height);
	buffer=new uint8_t[numBytes];

	// ��pFrameRGB�и�ͼ��λ�渳����ʵĻ�����
	avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,
    pCodecCtx->width, pCodecCtx->height);
	return true;

}
void CVideo::DrawVideo(void)
{

	glBindTexture(GL_TEXTURE_2D, VideoTexID);
 int tmpXX=isend;

	while(av_read_frame(pFormatCtx, &packet)>=0)
	{
		isend=isend+1;
		// ������Ƶ���е�һ������
		if(packet.stream_index==videoStream)
		{
			// ������Ƶ��
			avcodec_decode_video(pCodecCtx, pFrame, &frameFinished, 
				packet.data, packet.size);

			// ���ǵõ�һ֡����
			if(frameFinished)
			{
				// ��ԭʼͼ��ת���� RGB
				img_convert((AVPicture *)pFrameRGB, PIX_FMT_RGB24, 
					(AVPicture*)pFrame, pCodecCtx->pix_fmt, pCodecCtx->width, 
					pCodecCtx->height);

				// ������Ƶ֡�����̵ȵȣ�
				//DoSomethingWithTheImage(pFrameRGB);
				break;

			}
		}

		// �ͷ���av_read_frame����ռ�İ�
		av_free_packet(&packet);
	}

	//
	TTTTT=(AVPicture *)pFrameRGB;
	ww=pCodecCtx->width;

	if(tmpXX==isend)
	{
		isend=0;
		avcodec_flush_buffers(pFormatCtx->streams[videoStream]->codec);
		av_seek_frame(pFormatCtx, -1, pFormatCtx->start_time, 0);
	}
	hh=pCodecCtx->height;
	glTexSubImage2D(GL_TEXTURE_2D,0,0,0,ww,hh,GL_RGB,GL_UNSIGNED_BYTE,TTTTT->data[0]);
	glBindTexture(GL_TEXTURE_2D, 0);
}
