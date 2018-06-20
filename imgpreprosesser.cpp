#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

#include <string.h>
#include <iostream>

#define FILE_NAME_LENGTH

using namespace cv;
using namespace std;

char filename0[256]={0}, filename1[256]={0};

cv::Mat org,dst,img,tmp;
void on_mouse(int event,int x,int y,int flags,void *ustc)//eventÊó±êÊÂŒþŽúºÅ£¬x,yÊó±ê×ø±ê£¬flagsÍÏ×§ºÍŒüÅÌ²Ù×÷µÄŽúºÅ
{
    static Point pre_pt = cv::Point(-1,-1);//³õÊŒ×ø±ê
    static Point cur_pt = cv::Point(-1,-1);//ÊµÊ±×ø±ê
    char temp[16];
    if (event == EVENT_LBUTTONDOWN)//×óŒü°ŽÏÂ£¬¶ÁÈ¡³õÊŒ×ø±ê£¬²¢ÔÚÍŒÏñÉÏžÃµãŽŠ»®Ô²
    {
        org.copyTo(img);//œ«Ô­ÊŒÍŒÆ¬žŽÖÆµœimgÖÐ
        sprintf(temp,"(%d,%d)",x,y);
        pre_pt = Point(x,y);
        putText(img,temp,pre_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255),1,8);//ÔÚŽ°¿ÚÉÏÏÔÊŸ×ø±ê
        circle(img,pre_pt,2,Scalar(255,0,0,0),FILLED,8,0);//»®Ô²
        imshow("img",img);
    }
    else if (event == EVENT_MOUSEMOVE && !(flags & EVENT_FLAG_LBUTTON))//×óŒüÃ»ÓÐ°ŽÏÂµÄÇé¿öÏÂÊó±êÒÆ¶¯µÄŽŠÀíº¯Êý
    {
        img.copyTo(tmp);//œ«imgžŽÖÆµœÁÙÊ±ÍŒÏñtmpÉÏ£¬ÓÃÓÚÏÔÊŸÊµÊ±×ø±ê
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));//Ö»ÊÇÊµÊ±ÏÔÊŸÊó±êÒÆ¶¯µÄ×ø±ê
        imshow("img",tmp);
    }
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))//×óŒü°ŽÏÂÊ±£¬Êó±êÒÆ¶¯£¬ÔòÔÚÍŒÏñÉÏ»®ŸØÐÎ
    {
        img.copyTo(tmp);
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));
        rectangle(tmp,pre_pt,cur_pt,Scalar(0,255,0,0),1,8,0);//ÔÚÁÙÊ±ÍŒÏñÉÏÊµÊ±ÏÔÊŸÊó±êÍÏ¶¯Ê±ÐÎ³ÉµÄŸØÐÎ
        imshow("img",tmp);
    }
    else if (event == EVENT_LBUTTONUP)//×óŒüËÉ¿ª£¬œ«ÔÚÍŒÏñÉÏ»®ŸØÐÎ
    {
        org.copyTo(img);
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        putText(img,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));
        circle(img,pre_pt,2,Scalar(255,0,0,0),FILLED,8,0);
        rectangle(img,pre_pt,cur_pt,Scalar(0,255,0,0),1,8,0);//žùŸÝ³õÊŒµãºÍœáÊøµã£¬œ«ŸØÐÎ»­µœimgÉÏ
        imshow("img",img);
        img.copyTo(tmp);
        //œØÈ¡ŸØÐÎ°üÎ§µÄÍŒÏñ£¬²¢±£ŽæµœdstÖÐFILE_NAME_LENGTH
        int width = abs(pre_pt.x - cur_pt.x);
        int height = abs(pre_pt.y - cur_pt.y);
        if (width == 0 || height == 0)
        {
            printf("width == 0 || height == 0");
            return;
        }
        dst = org(Rect(min(cur_pt.x,pre_pt.x),min(cur_pt.y,pre_pt.y),width,height));
        cv::resize(dst,dst,Size(28,28));
        cvtColor( dst, dst, COLOR_BGR2GRAY );
        threshold(dst, dst, 170, 255, THRESH_BINARY);
        imwrite(filename1,dst);//×¢Òâœ«ÕâÀïžÄÎª×ÔŒºµÄŽŠÀíœá¹ûŽæŽ¢µØÖ·
        namedWindow("dst");
        imshow("dst",dst);
        waitKey(0);
    }
}
int main(int argc, char **argv)
{
    int i;
    cout << "argc: " << argc << endl;
    for(i=0; i<argc; i++)
        cout << argv[i] << " ";
    if(argc != 3){
        cout << "Usage: " << argv[0] << " [src img] [dst img]\n";
        exit(0);
    }
    strcpy(filename0, argv[1]);
    strcpy(filename1, argv[2]);
    cout << "from: " << filename0 << " to: " << filename1 << endl;
    
    org = imread(filename0);//¶ÁÈ¡ÍŒÆ¬µØÖ·
    org.copyTo(img);
    org.copyTo(tmp);
    namedWindow("img");//¶šÒåÒ»žöimgŽ°¿Ú
    setMouseCallback("img",on_mouse,0);//µ÷ÓÃ»Øµ÷º¯Êý
    imshow("img",img);
    cv::waitKey(0);
}
