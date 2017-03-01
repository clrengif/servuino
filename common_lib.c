/*  Servuino is a Arduino Simulator Engine
    Copyright (C) 2012  Benny Saxen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



//====================================
char *int2bin(int num, int pad)
// Example: printf("%s\n", int2bin(i, 8));
//====================================
{
  char *str = (char*)malloc(sizeof(char) * (pad + 1));
  if (str)
  {
    str[pad] = '\0';
    while (--pad >= 0)
    {
      str[pad] = num & 1 ? '1' : '0';
      num >>= 1;
    }
  }
  else
  {
    printf("int2bin:No string\n");
  }
  return str;
}
