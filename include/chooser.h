
#ifndef CHOOSER_H
#define CHOOSER_H

class Chooser {
  private:
  char count;
  char curr;

  public:
  Chooser(char count, char start = 0);

  char current() const;
  void nextChoice();
  void previousChoice();
};

#endif  // CHOOSER_H