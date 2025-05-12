#ifndef CHOOSER_H
#define CHOOSER_H

class Chooser {
  private:
  char count;
  char curr;
  char start;

  public:
  Chooser(char count, char start = 0);

  char current();
  void nextChoice();
  void previousChoice();
  void reset();
};

// Declare chooser as extern
extern Chooser chooser;

#endif  // CHOOSER_H