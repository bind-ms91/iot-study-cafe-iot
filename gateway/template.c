#include "template.h"

#include <stdlib.h> // malloc(), free()

Template* template_new() {
  Template* template = malloc(sizeof(template));
  return template;
}

void template_delete(Template* template) {
  free(template);
}
