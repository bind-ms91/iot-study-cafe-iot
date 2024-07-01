#include "template.h"

#include <stdlib.h> // malloc(), free()

Template* template_new() {
  return template_new_argument(defaultArgument);
}

Template* template_new_argument(Argument argument) {
  Template* template = malloc(sizeof(template));
  return template;
}

void template_delete(Template* template) {
  free(template);
}
