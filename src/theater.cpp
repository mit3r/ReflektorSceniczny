#include "api/theater.h"

Queue<Animation::Timeline> Theater::queue = Queue<Animation::Timeline>(Theater::MAX_QUEUE);  // Queue of animations
unsigned char Theater::index = 0;                                                            //
bool Theater::animating = false;

void Theater::handle() {
  if (queue.isEmpty()) return;
  if (Movement::isMoving() || Lights::isFading()) return;

  if (queue.front()->size == 0 || queue.front()->size > Animation::MAX_FRAMES || index >= queue.front()->size)
    return Theater::skip();

  Animation::Frame *frame = &queue.front()->frames[index];
  unsigned long duration = frame->modifier & Animation::MASK_DURATION;
  bool keepPosition = frame->modifier & Animation::Modifier::KEEP_POSITION;
  bool keepLight = frame->modifier & Animation::Modifier::KEEP_LIGHT;
  // bool wait = pointer->frames[index].modifier & Animation::Modifier::WAITFORCOMMAND;

  if (!Movement::moveToAngle(keepPosition ? Movement::getTargetAngle() : frame->point)) return;
  if (!Lights::fadeColorTo(keepLight ? Lights::getTargetColor() : frame->color, duration)) return;

  index++;
}

void Theater::setup() {
  static Ticker ticker;
  ticker.attach_ms(40, Theater::handle);
}

bool Theater::run(Animation::Timeline animation) {
  return queue.enqueue(animation);
}

void Theater::skip() {
  queue.dequeue();
  index = 0;

  Movement::stop();
  Lights::stop();
}

bool Theater::isAnimating() {
  return !queue.isEmpty();
}
