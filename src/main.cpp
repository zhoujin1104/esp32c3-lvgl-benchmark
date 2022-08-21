#include <Arduino.h>
#include <lvgl.h>
#include "../demos/lv_demos.h"
#include "main.h"

TFT_eSPI tft = TFT_eSPI();

static lv_disp_draw_buf_t draw_buf;
static lv_color_t lbuf[TFT_HEIGHT * 10];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();//使能写功能
  tft.setAddrWindow(area->x1, area->y1, w, h);//设置填充区域
  tft.pushColors((uint16_t *)&color_p->full, w * h, true); //写入颜色缓存和缓存大小
  tft.endWrite();//关闭写功能

  lv_disp_flush_ready(disp); //调用区域填充颜色函数
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("hello esp32c3");
  initTFT();
  initLEDs();
  lv_init();
  lv_disp_draw_buf_init(&draw_buf, lbuf, NULL, TFT_HEIGHT * 10);
/*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
/*Change the following line to your display resolution*/
  disp_drv.hor_res = TFT_HEIGHT;
  disp_drv.ver_res = TFT_WIDTH;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
#if 0
  lv_obj_t *label = lv_label_create(lv_scr_act());
  String Version = "Hello lvgl 8.2.0" ;
  lv_label_set_text(label, Version.c_str());
  lv_obj_align(label, LV_ALIGN_DEFAULT, 0, 0);
#else
  lv_demo_benchmark();
#endif



}

void loop() {
  // put your main code here, to run repeatedly:
  lv_task_handler();
  //lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}