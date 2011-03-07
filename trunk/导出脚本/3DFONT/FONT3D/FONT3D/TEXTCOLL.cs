using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace FONT3D
{
    static class TEXTCOLL
    {
        static public string GetStrs(string[] fname)
        {
            string ts = "";
            foreach (string fnam in fname)
            {
                ts += getStr(fnam);
            }
            return Reduce(ts);
        }

        static public string getStr(string fname, Encoding e)
        {
            return Reduce(File.ReadAllText(fname, e));
        }

        static public string getStr(string fname)
        {
            return Reduce(File.ReadAllText(fname));
        }

        static public string Reduce(string strs)
        {
            List<char> sb = new List<char>();
            char[] tchs = strs.ToCharArray();
            for (int i = 0; i < strs.Length; i++)
            {
                if (!sb.Contains(tchs[i]))
                {
                    sb.Add(tchs[i]);
                }
            }
            sb.Sort();
            return (new string(sb.ToArray())).Replace("\r", "").Replace("\n", "").Replace("\t", "");
        }

    }
}
