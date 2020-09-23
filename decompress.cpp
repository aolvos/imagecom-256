byte *load_bin_image(int res)
{
    int cpos, x = 0, y = 0, rtime = 0, cnum = 0;
    byte r, g, b, a;

    HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(res), RT_RCDATA);
    HGLOBAL hMemory = LoadResource(hModule, hResource);
    DWORD dwSize = SizeofResource(hModule, hResource);
    LPVOID lpAddress = LockResource(hMemory);
    byte *bytes = (byte*)malloc(dwSize);
    memcpy(bytes, lpAddress, dwSize);

    xres[res] = bytes[0] + bytes[1] * 256;
    yres[res] = bytes[2] + bytes[3] * 256;
    byte *buf = (byte*)malloc(xres[res] * yres[res] * 4 + 1);
    cpos = bytes[4] * 3 + 5;
    for (int i = cpos; y < yres[res]; i++)
    {
        a = 255;
        if (bytes[i] == 0)
        {
            i++;
            rtime = bytes[i] + bytes[i + 1] * 256 + bytes[i + 2] * 65536;
            i+=3;
            cnum = bytes[i] - 1;
            r = bytes[cnum * 3 + 5];
            g = bytes[cnum * 3 + 6];
            b = bytes[cnum * 3 + 7];
            if ((r == 0) && (g == 255) && (b == 255))
            {
                a = 0;
            }
            while (rtime > 0)
            {
                buf[(y * xres[res] * 4) + (x * 4)] = b;
                buf[(y * xres[res] * 4) + (x * 4) + 1] = g;
                buf[(y * xres[res] * 4) + (x * 4) + 2] = r;
                buf[(y * xres[res] * 4) + (x * 4) + 3] = a;
                rtime--;
                x++;
                if (x == xres[res])
                {
                    y++;
                    x = 0;
                }
            }
        }
        else
        {
            cnum = bytes[i] - 1;
            r = bytes[cnum * 3 + 5];
            g = bytes[cnum * 3 + 6];
            b = bytes[cnum * 3 + 7];
            if ((r == 0) && (g == 255) && (b == 255))
            {
                a = 0;
            }
            buf[(y * xres[res] * 4) + (x * 4)] = b;
            buf[(y * xres[res] * 4) + (x * 4) + 1] = g;
            buf[(y * xres[res] * 4) + (x * 4) + 2] = r;
            buf[(y * xres[res] * 4) + (x * 4) + 3] = a;
            x++;
            if (x == xres[res])
            {
                y++;
                x = 0;
            }
        }
    }
    free(bytes);
    return buf;
}