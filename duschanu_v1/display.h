void updateScreen (int number) {

  //Create a new image cache
  UBYTE *BlackImage;
  /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
  UWORD Imagesize = ((EPD_2IN13_V2_WIDTH % 8 == 0) ? (EPD_2IN13_V2_WIDTH / 8 ) : (EPD_2IN13_V2_WIDTH / 8 + 1)) * EPD_2IN13_V2_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while (1);
  }
  printf("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, EPD_2IN13_V2_WIDTH, EPD_2IN13_V2_HEIGHT, 270, WHITE);
  Paint_SelectImage(BlackImage);
  Paint_SetMirroring(MIRROR_HORIZONTAL); //
  Paint_Clear(WHITE);

  printf("Drawing\r\n");
  //1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  Paint_DrawString_EN(140, 15, "Duscha Nu", &Font16, BLACK, WHITE);
  Paint_DrawNum(140, 40, number, &Font16, BLACK, WHITE);

  EPD_2IN13_V2_Display(BlackImage);
  DEV_Delay_ms(2000);
  
  printf("Goto Sleep...\r\n");
  EPD_2IN13_V2_Sleep();
  
  free(BlackImage);
  BlackImage = NULL;
  DEV_Delay_ms(1000);//Analog clock 1s
}

void setupScreen() {
  DEV_Module_Init();

  printf("e-Paper Init and Clear...\r\n");
  EPD_2IN13_V2_Init(EPD_2IN13_V2_FULL);
  EPD_2IN13_V2_Clear();
  DEV_Delay_ms(500);


}
