/**
 * \file Type.cpp
 *
 * \author Joseph Kasza
 */

#include "pch.h"
#include "Type.h"
#include <string> 

using namespace std;
using namespace Gdiplus;

const std::wstring ImageDirectory = L"images/";


void CType::AddImage(std::wstring filename)
{
    std::wstring realName = ImageDirectory + filename;
    // Create a bitmap image and load the file into it.
    auto image = shared_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(realName.c_str()));
    if (image->GetLastStatus() != Ok)
    {
        std:: wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
        return;
    }
    mImages.push_back(image);
}
