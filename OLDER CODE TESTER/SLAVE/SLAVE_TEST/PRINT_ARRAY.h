//
//
//=========================<<<PRINT_DATA>>>=========================

// PRINT         : PRINT ARRAY ONLY.

#pragma once
template <typename T, size_t N>
void PRINT(T (&ARRAY)[N]) 
{
  for (uint64_t i = 0; i < N; i++) {
    if (N > 32) break;
    if (sizeof(T) == 1)Serial.print(ARRAY[i], DEC);
    if (sizeof(T) >  1)Serial.print(ARRAY[i]);
    Serial.print(" ");
  }
  Serial.println();
}
