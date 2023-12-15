#include "OneWireNg_CurrentPlatform.h"
#include "drivers/DSTherm.h"
#include "utils/Placeholder.h"

static Placeholder<OneWireNg_CurrentPlatform> ow;
DSTherm drv(ow);

/*double getTemperature(const DSTherm::Scratchpad& scrpd)
{
  
  double tempD=scrpd.getTemp()/1000.0;
  //Serial1.println(tempD,3);
  return tempD;
}*/

double getTemperature()
{  /* convert temperature on all sensors connected... */
  drv.convertTempAll(DSTherm::MAX_CONV_TIME);
  static Placeholder<DSTherm::Scratchpad> scrpd;
  OneWireNg::ErrorCode ec = drv.readScratchpadSingle(scrpd);
  DSTherm::Scratchpad scrpd2=scrpd;
  if (ec == OneWireNg::EC_SUCCESS)
  {
      return scrpd2.getTemp()/1000.0;
  }
  else if (ec == OneWireNg::EC_CRC_ERROR)
  {
    return OneWireNg::EC_CRC_ERROR;
  }
  else return 0;
}
//########################################
void setup()
{
  new (&ow) OneWireNg_CurrentPlatform(PIN_PD7, false);
  Serial1.begin(9600);

/*#if (CONFIG_MAX_SEARCH_FILTERS > 0)//????????
    drv.filterSupportedSlaves();
#endif*/
}

void loop()
{
  Serial1.println(getTemperature(),3);
  delay(1000);
}
