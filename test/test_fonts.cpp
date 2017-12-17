/* example1.c                                                      */
/*                                                                 */
/* This small program shows how to print a rotated string with the */
/* FreeType 2 library.                                             */


#include "font/fonts.hpp"
#include "font/synthesis.hpp"
#include "opencv2/opencv.hpp"
using namespace Beta;
using namespace cv;


int main(int argc, char* argv []){
  
  int height = 64;
  int width  = 64;
  // Fonts* font = new Fonts(height, width);
  // font->init("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-BI.ttf");
  // font->draw("A",0);
  // Mat img = font->get();
  // imshow("src",img);
  // waitKey(0);
  // imwrite("font.png", img);

  string path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/local_binary_regression/data/";
  Synthesis* syn = new Synthesis("fonts.txt",path);
  syn->init();
  syn->run();
  syn->destroy();
  return 0;
}


