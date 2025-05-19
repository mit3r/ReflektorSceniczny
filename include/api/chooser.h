#ifndef CHOOSER_H
#define CHOOSER_H

class Chooser {
  private:
  unsigned char count;
  unsigned char curr;
  unsigned char start;

  public:
  Chooser(unsigned char count, unsigned char start = 0);

  unsigned char current();
  void nextChoice();
  void previousChoice();
  void reset();
};

// Declare chooser as extern
extern Chooser chooser;

#endif  // CHOOSER_H