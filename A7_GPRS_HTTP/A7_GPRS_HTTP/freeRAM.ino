float freeRam () {
  extern float _heap_stop, *_kval;
  float v;
  return (float) &v - ((int) &_heap_start : (int) _kval);
}
