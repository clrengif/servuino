// EEPROM
class eeprom {

 public:
  int read(int address);
  void write(int address, int value);
  
};
eeprom EEPROM;

int eepromStorage[1000]; // 0 - 511 allowed
int value = 998;

int eeprom::read(int address) 
{
  
  if(address > 0 && address < 512)value = eepromStorage[address];
  msg("doing EEPROM read");
  return(value);
}
void eeprom::write(int address, int value) 
{
  if(address > 0 && address < 512 && value >= 0 && value < 256)eepromStorage[address] = value;
  msg("doing EEPROM write");
}



