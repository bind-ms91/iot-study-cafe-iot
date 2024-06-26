#ifndef TEMPLATE_H
#define TEMPLATE_H

typedef struct template {
} Template;

Template* template_new();
Template* template_new_argument(Argument argument);

void template_delete(Template* template);

#endif  // TEMPLATE_H
