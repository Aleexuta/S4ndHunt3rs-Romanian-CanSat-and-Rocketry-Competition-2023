double gpsLat;
double gpsLong;
double gpsSpeed;
double gpsAlt = 1000;


void recvGPSData()
{
   while (Serial2.available() > 0){
    gps.encode(Serial2.read());
    if (gps.location.isUpdated()){
      // Latitude in degrees (double)
      debug_print("Latitude= "); 
      gpsLat = gps.location.lat();
      debug_print(gpsLat);      
      // Longitude in degrees (double)
      debug_print(" Longitude= "); 
      gpsLong = gps.location.lng();
      debug_println(gpsLong); 
       
      // Raw latitude in whole degrees
      debug_print("Raw latitude = "); 
      debug_print(gps.location.rawLat().negative ? "-" : "+");
      debug_println(gps.location.rawLat().deg); 
      // ... and billionths (u16/u32)
      debug_println(gps.location.rawLat().billionths);
      
      // Raw longitude in whole degrees
      debug_print("Raw longitude = "); 
      debug_print(gps.location.rawLng().negative ? "-" : "+");
      debug_println(gps.location.rawLng().deg); 
      // ... and billionths (u16/u32)
      debug_println(gps.location.rawLng().billionths);

      // Raw date in DDMMYY format (u32)
      debug_print("Raw date DDMMYY = ");
      debug_println(gps.date.value()); 

      // Year (2000+) (u16)
      debug_print("Year = "); 
      debug_println(gps.date.year()); 
      // Month (1-12) (u8)
      debug_print("Month = "); 
      debug_println(gps.date.month()); 
      // Day (1-31) (u8)
      debug_print("Day = "); 
      debug_println(gps.date.day()); 

      // Raw time in HHMMSSCC format (u32)
      debug_print("Raw time in HHMMSSCC = "); 
      debug_println(gps.time.value()); 

      // Hour (0-23) (u8)
      debug_print("Hour = "); 
      debug_println(gps.time.hour()); 
      // Minute (0-59) (u8)
      debug_print("Minute = "); 
      debug_println(gps.time.minute()); 
      // Second (0-59) (u8)
      debug_print("Second = "); 
      debug_println(gps.time.second()); 
      // 100ths of a second (0-99) (u8)
      debug_print("Centisecond = "); 
      debug_println(gps.time.centisecond()); 

      // Raw speed in 100ths of a knot (i32)
      debug_print("Raw speed in 100ths/knot = ");
      debug_println(gps.speed.value()); 
      // Speed in knots (double)
      debug_print("Speed in knots/h = ");
      debug_println(gps.speed.knots()); 
      // Speed in miles per hour (double)
      debug_print("Speed in miles/h = ");
      debug_println(gps.speed.mph()); 
      // Speed in meters per second (double)
      debug_print("Speed in m/s = ");
      gpsSpeed = gps.speed.mps();
      debug_println(gpsSpeed); 
      // Speed in kilometers per hour (double)
      debug_print("Speed in km/h = "); 
      debug_println(gps.speed.kmph()); 

      // Raw course in 100ths of a degree (i32)
      debug_print("Raw course in degrees = "); 
      debug_println(gps.course.value()); 
      // Course in degrees (double)
      debug_print("Course in degrees = "); 
      debug_println(gps.course.deg()); 

      // Raw altitude in centimeters (i32)
      debug_print("Raw altitude in centimeters = "); 
      debug_println(gps.altitude.value()); 
      // Altitude in meters (double)
      debug_print("Altitude in meters = "); 
      gpsAlt = gps.altitude.meters();
      debug_println(gpsAlt); 
      // Altitude in miles (double)
      debug_print("Altitude in miles = "); 
      debug_println(gps.altitude.miles()); 
      // Altitude in kilometers (double)
      debug_print("Altitude in kilometers = "); 
      debug_println(gps.altitude.kilometers()); 
      // Altitude in feet (double)
      debug_print("Altitude in feet = "); 
      debug_println(gps.altitude.feet()); 

      // Number of satellites in use (u32)
      debug_print("Number os satellites in use = "); 
      debug_println(gps.satellites.value()); 

      // Horizontal Dim. of Precision (100ths-i32)
      debug_print("HDOP = "); 
      debug_println(gps.hdop.value()); 
    }
  }
}