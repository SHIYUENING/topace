using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace FONT3D
{
    public class Font3D
    {
        struct VT3
        {
            public float x, y, z;
        }
        struct FACE
        {
            public int x, y, z;
        }

        struct CHAR3D
        {
            public int code;
            public string value;
            public VT3[] verts;
            public VT3[] normals;
            public FACE[] faces;
        }

        private byte[] Head;
        private const int Verson = 3;

        //private int filesize;
        private int pageCode; //1200 unicode
        private int charscount;
        public int CharCount
        {
            get { return charscount; }
        }

        public int GetCharNum()
        {
            return charscount;
        }

        public string GetChar(int i)
        {
            return chs[i].value;
        }

        public void GetTmpFile(string tmpf)
        {
            BinaryReader r = new BinaryReader(File.OpenRead(tmpf));
            r.ReadInt32();
            for (int idx = 0; idx < charscount; idx++)
            {
                int vtnum = r.ReadInt32();
                int fnum = r.ReadInt32();
                chs[idx].verts = new VT3[vtnum];
                chs[idx].normals = new VT3[vtnum];
                chs[idx].faces = new FACE[fnum];
                for (int i = 0; i < vtnum; i++)
                {
                    chs[idx].verts[i].x = r.ReadSingle();
                    chs[idx].verts[i].y = r.ReadSingle();
                    chs[idx].verts[i].z = r.ReadSingle();
                }
                for (int i = 0; i < vtnum; i++)
                {
                    chs[idx].normals[i].x = r.ReadSingle();
                    chs[idx].normals[i].y = r.ReadSingle();
                    chs[idx].normals[i].z = r.ReadSingle();
                }
                for (int i = 0; i < fnum; i++)
                {
                    chs[idx].faces[i].x = r.ReadInt32();
                    chs[idx].faces[i].y = r.ReadInt32();
                    chs[idx].faces[i].z = r.ReadInt32();
                }
            }
            r.Close();
            try
            {
                File.Delete(tmpf);
            }
            catch
            { }
        }

        public void SetCharVert(int idx, float[] xyz)
        {
            chs[idx].verts = new VT3[xyz.Length / 3];
            for (int i = 0; i < xyz.Length / 3; i++)
            {
                chs[idx].verts[i].x = xyz[i * 3 + 0];
                chs[idx].verts[i].y = xyz[i * 3 + 1];
                chs[idx].verts[i].z = xyz[i * 3 + 2];
            }
        }


        public void SetCharNormal(int idx, float[] xyz)
        {
            chs[idx].normals = new VT3[xyz.Length / 3];
            for (int i = 0; i < xyz.Length / 3; i++)
            {
                chs[idx].normals[i].x = xyz[i * 3 + 0];
                chs[idx].normals[i].y = xyz[i * 3 + 1];
                chs[idx].normals[i].z = xyz[i * 3 + 2];
            }
        }


        public void SetCharFace(int idx, int[] xyz)
        {
            chs[idx].faces = new FACE[xyz.Length / 3];
            for (int i = 0; i < xyz.Length / 3; i++)
            {
                chs[idx].faces[i].x = xyz[i * 3 + 0];
                chs[idx].faces[i].y = xyz[i * 3 + 1];
                chs[idx].faces[i].z = xyz[i * 3 + 2];
            }
        }

        public void savefile(string fname)
        {
            //MemoryStream ms = new MemoryStream();
            BinaryWriter w = new BinaryWriter(File.Create(fname));
            w.Write(Head);
            w.Write(Verson);
            w.Write(0);

            w.Write(pageCode);
            w.Write(charscount);
            w.Write(0); w.Write(0);

            for (int i = 0; i < 0x10000; i++)
            {
                w.Write(0); w.Write(0); w.Write(0);
            }

            //MemoryStream vtms = new MemoryStream();
            BinaryWriter vw = new BinaryWriter(File.Create(fname + ".ttmp"));

            for (int i = 0; i < charscount; i++)
            {
                w.BaseStream.Position = 0x20 + chs[i].code * 0xC;
                w.Write((int)vw.BaseStream.Length + 0xC0020);
                w.Write(chs[i].verts.Length);
                w.Write(chs[i].faces.Length);
                for (int j = 0; j < chs[i].verts.Length; j++)
                {
                    vw.Write(chs[i].verts[j].x);
                    vw.Write(chs[i].verts[j].y);
                    vw.Write(chs[i].verts[j].z);
                }
                for (int j = 0; j < chs[i].normals.Length; j++)
                {
                    vw.Write(chs[i].normals[j].x);
                    vw.Write(chs[i].normals[j].y);
                    vw.Write(chs[i].normals[j].z);
                }
                for (int j = 0; j < chs[i].faces.Length; j++)
                {
                    vw.Write(chs[i].faces[j].x);
                    vw.Write(chs[i].faces[j].y);
                    vw.Write(chs[i].faces[j].z);
                }
                vw.Flush();
            }
            vw.Flush();
            vw.Close();

            w.BaseStream.Position = w.BaseStream.Length;

            FileStream fs = File.OpenRead(fname + ".ttmp");
            byte[] xxx = new byte[0x1000];

            int readedb = 0;
            int offset=0;
            fs.Position = 0;
            while (true)
            {
                readedb = fs.Read(xxx, 0, 0x1000);
                if (readedb <1) break;
                w.Write(xxx, 0, readedb);
                offset += readedb;
            }
            fs.Close();
            File.Delete(fname + ".ttmp");
            //w.Write(vtms.ToArray());
            w.BaseStream.Position = 0xc;
            w.Write((int)w.BaseStream.Length);
            w.Flush();
            //File.WriteAllBytes(fname, ms.ToArray());
            w.Close();
        }

        private CHAR3D[] chs;

        public Font3D()
        {
            Head = new byte[] { (byte)'T', (byte)'A', (byte)'M', (byte)'F', (byte)'T', (byte)'3', (byte)'D', 0 };
            //filesize = 0;
            pageCode = 1200;

            string temstr = TEXTCOLL.Reduce(CODETBL.unicode);

            //charscount = CODETBL.unicode.Length;
            charscount = temstr.Length;
            chs = new CHAR3D[charscount];
            //char[] temchar = CODETBL.unicode.ToCharArray();
            char[] temchar = temstr.ToCharArray();
            for (int i = 0; i < charscount; i++)
            {
                chs[i].value = temchar[i].ToString();
                chs[i].code = temchar[i];
            }
        }


        public Font3D(string fontcharlist,int codepage)
        {
            Head = new byte[] { (byte)'T', (byte)'A', (byte)'M', (byte)'F', (byte)'N', (byte)'T', (byte)'3', (byte)'D' };
            //filesize = 0;
            pageCode = codepage;

            string temstr = TEXTCOLL.Reduce(File.ReadAllText(fontcharlist, Encoding.GetEncoding(codepage)));

            //charscount = CODETBL.unicode.Length;
            charscount = temstr.Length;
            chs = new CHAR3D[charscount];
            //char[] temchar = CODETBL.unicode.ToCharArray();
            char[] temchar = temstr.ToCharArray();
            for (int i = 0; i < charscount; i++)
            {
                chs[i].value = temchar[i].ToString();
                chs[i].code = temchar[i];
            }
        }



    }
}
