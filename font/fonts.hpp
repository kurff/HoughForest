#ifndef __FONT_HPP__
#define __FONT_HPP__

#include <stdio.h>
#include <string.h>
#include <math.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include "opencv2/opencv.hpp"

using namespace cv;

using namespace std;
namespace Beta{
    class Fonts{
        public:
            Fonts(int height, int width):height_(height), width_(width){
                error_ = FT_Init_FreeType( &library_ );
                img = Mat::zeros(height,width,CV_8UC1);
            }
            ~Fonts(){

            }

            void init(string font_type){
                error_ = FT_New_Face( library_, font_type.c_str(), 0, &face_ );
                error_ = FT_Set_Char_Size( face_, 50 * 64, 0,
                            100, 0 );                /* set character size */
                slot_ = face_->glyph;
            }

            void draw(string text){

                error = FT_Load_Char( face_, text[0], FT_LOAD_RENDER );
                draw_bitmap( &slot_->bitmap,
                 slot_->bitmap_left,
                 target_height - slot_->bitmap_top );
            }

        protected:
            
            FT_Library    library_;
            FT_Face       face_;

            FT_GlyphSlot  slot_;
            FT_Matrix     matrix_;                 /* transformation matrix */
            FT_Vector     pen_;                    /* untransformed origin  */
            FT_Error      error_;
            Mat img_ ;
            int height_;
            int width_;

    };








}






#endif