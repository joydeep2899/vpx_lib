#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
//#include "./video_reader.h"
#include "../libvpx/vpx/vpx_decoder.h"
#include "../libvpx/vpx/vp8cx.h"
#include "../libvpx/vpx/vp8dx.h"
#include "../libvpx/video_reader.h"

#include "../libvpx/tools_common.h"
#include "../libvpx/tools_common.c"
#include "../libvpx/vpx_config.h"
#include "../libvpx/video_reader.c"
#include "../libvpx/ivfdec.c"
#include "../libvpx/ivfdec.h"
#include "../libvpx/ivfenc.h"
#include "../libvpx/ivfenc.c"
#include "../libvpx/y4minput.h"

#include "../libvpx/y4minput.c"
#include "../libvpx/video_writer.h"
#include "../libvpx/video_writer.c"


static const char *exec_name;
int main()
{ int framecnt = 0 ;
FILE *outfname=NULL;
vpx_codec_ctx_t ctx;
VpxVideoReader *reader=NULL;


const VpxInterface *decoder;
const VpxVideoInfo *info;
 vpx_codec_iface_t *iface;
vpx_codec_flags_t flags;

vpx_codec_err_t errr;

outfname = fopen("hello.mp4", "wb");



reader=vpx_video_reader_open("vp82.ivf");
 if (!reader) printf("Failed to open  for reading.");
info=vpx_video_reader_get_info(reader);
decoder=get_vpx_decoder_by_fourcc(info->codec_fourcc);
errr=vpx_codec_dec_init(&ctx,decoder->codec_interface(),NULL,0);

printf("%d",info->codec_fourcc);


 //printf("%s",vpx_codec_err_to_string(errr));
while(vpx_video_reader_read_frame(reader))
  {
   vpx_codec_iter_t iter=NULL;
   vpx_image_t *img;
   size_t framesize=0;
   const char *frame= vpx_video_reader_get_frame(reader,&framesize);

  if(vpx_codec_decode(&ctx,frame,(unsigned int)framesize,NULL,0))
  printf("%s",frame);

  while((img=vpx_codec_get_frame(&ctx,&iter))!=NULL )
   {
    vpx_img_write(img,outfname);



    //printf("%s",img->img_data);
    framecnt++;

    //printf("%d ",framecnt);
   }




  }

 //printf("Play: ffplay -f rawvideo -pix_fmt yuv420p -s %dx%d %s\n",info->frame_width, info->frame_height, outfname);
  vpx_video_reader_close(reader);

  fclose(outfname);

return 0;
}
