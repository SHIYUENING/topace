#include "Video.h"

CVideo::CVideo(void)
:isend(0)
,VideoTexID(0)
,isLoop(false)
,isPlaying(false)
{
}

CVideo::~CVideo(void)
{
}
void CVideo::InitVideo(void)
{
/*
	unsigned int* data;						// 存储数据

	// 为纹理数据（wh*wh*4）建立存储区
	data = (unsigned int*)new GLuint[((VideoTexSize * VideoTexSize)* 3 * sizeof(unsigned int))];
	ZeroMemory(data,((VideoTexSize * VideoTexSize)* 3 * sizeof(unsigned int)));	// 清除存储区

	glGenTextures(1, &VideoTexID);				// 创建一个纹理
	glBindTexture(GL_TEXTURE_2D, VideoTexID);			// 构造纹理
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, VideoTexSize, VideoTexSize, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	

	delete [] data;						// 释放数据
	*/
	av_register_all();
}
bool CVideo::LoadVideo(const char *filename,bool loop)
{
	isLoop=loop;
	
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

// 打开解码器
	if(avcodec_open(pCodecCtx, pCodec)<0)
	{
		MessageBox(NULL,"cant avcodec_open.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		return false;
	}





	pFrame=avcodec_alloc_frame();

	pFrameRGB=avcodec_alloc_frame();

	int     numBytes;
	

	numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
    pCodecCtx->height);
	
	buffer=new uint8_t[numBytes];

	// 在pFrameRGB中给图象位面赋予合适的缓冲区
	avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,
    pCodecCtx->width, pCodecCtx->height);
	isPlaying=true;
	EmptyTextureRGB(max(pCodecCtx->width, pCodecCtx->height));
	return true;

}
void CVideo::DrawVideo(void)
{

	if(!isPlaying)
	{
		LoadVideo("Data/video/PSS_1.wmv");
		return;
	}
	glBindTexture(GL_TEXTURE_2D, VideoTexID);
 int tmpXX=isend;

	while(av_read_frame(pFormatCtx, &packet)>=0)
	{
		isend=isend+1;
		// 这是视频流中的一个包吗？
		if(packet.stream_index==videoStream)
		{
			// 解码视频流
			avcodec_decode_video(pCodecCtx, pFrame, &frameFinished, 
				packet.data, packet.size);

			// 我们得到一帧了吗？
			if(frameFinished)
			{
				// 把原始图像转换成 RGB
				img_convert((AVPicture *)pFrameRGB, PIX_FMT_RGB24, 
					(AVPicture*)pFrame, pCodecCtx->pix_fmt, pCodecCtx->width, 
					pCodecCtx->height);

				av_free_packet(&packet);
				// 处理视频帧（存盘等等）
				//DoSomethingWithTheImage(pFrameRGB);
				break;

			}
		}

		// 释放用av_read_frame分配空间的包
		av_free_packet(&packet);
	}

	//avcodec_close(pCodecCtx);
	TTTTT=(AVPicture *)pFrameRGB;
	ww=pCodecCtx->width;

	if(tmpXX==isend)
	{

		if(isLoop)
		{
			isend=0;
			avcodec_flush_buffers(pFormatCtx->streams[videoStream]->codec);
			av_seek_frame(pFormatCtx, -1, pFormatCtx->start_time, 0);
		}
		else
		{
			isPlaying=false;
			FreeVideo();
			return;
		}
	}
	hh=pCodecCtx->height;
	glTexSubImage2D(GL_TEXTURE_2D,0,0,0,ww,hh,GL_RGB,GL_UNSIGNED_BYTE,TTTTT->data[0]);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CVideo::FreeVideo(void)
{

	if(VideoTexID!=0)
	{
		glDeleteTextures(1,&VideoTexID);
		VideoTexID=0;
	}
		
	av_free(pFrameRGB);

	 

	// Free the YUV frame

	av_free(pFrame);

	 
	av_free(buffer);

	// Close the codec

	avcodec_close(pCodecCtx);

	 

	// Close the video file

	av_close_input_file(pFormatCtx);
}

unsigned int CVideo::EmptyTextureRGB(unsigned int VideoSize)
{
	unsigned int VideoTexSize=32;
	while(VideoTexSize<VideoSize)
		VideoTexSize=VideoTexSize*2;

	if(VideoTexID!=0)
	{
		glDeleteTextures(1,&VideoTexID);
		VideoTexID=0;
	}
/*
	char WaringString[64]={0};
	sprintf(WaringString,"VideoTexSize %d,VideoSize %d",VideoTexSize,VideoSize);
	::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
	*/
	unsigned int* data;						// 存储数据

	// 为纹理数据（wh*wh*4）建立存储区
	data = (unsigned int*)new GLuint[((VideoTexSize * VideoTexSize)* 3 * sizeof(unsigned int))];
	ZeroMemory(data,((VideoTexSize * VideoTexSize)* 3 * sizeof(unsigned int)));	// 清除存储区

	glGenTextures(1, &VideoTexID);				// 创建一个纹理
	glBindTexture(GL_TEXTURE_2D, VideoTexID);			// 构造纹理
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, VideoTexSize, VideoTexSize, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	delete [] data;						// 释放数据
	return VideoTexID;
}
