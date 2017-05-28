 //This define micro controllers port for LCD connection
#define DS18B20_PORT PORTD
#define DS18B20_DDR DDRD
#define DS18B20_PIN PIND
#define ONE_WIRE_PIN 2

#define DS18B20_PIN_0 DS18B20_DDR|=(1<<ONE_WIRE_PIN), DS18B20_PORT&=~(1<<ONE_WIRE_PIN)
#define DS18B20_PIN_1 DS18B20_DDR&=~(1<<ONE_WIRE_PIN), DS18B20_PORT&=~(1<<ONE_WIRE_PIN)

//Sensor initialization, if successful, return true(for example: if(ds18b20_init){Blahblahblah;})
_Bool ds18b20_init();

//Send command in sensor (the details read in data sheet)
void ds18b20_write_byte(char command);

//Read byte from sensor, return read byte
unsigned char ds18b20_read_byte();

//Write scratchpad of sensor
void ds18b20_write_scrathpad(unsigned char scratchpad[]);

//Temperature calculate, return temperature value
float ds18b20_temperature_calculate(unsigned char scratchpad[]);

//CRC calculate, return true, if the data read is correct
_Bool ds18b20_crc_calculate(unsigned char scratchpad[]);
