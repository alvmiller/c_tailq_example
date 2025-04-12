#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

// https://man7.org/linux/man-pages/man3/tailq.3.html

struct entry {
    int data;
    TAILQ_ENTRY(entry) entries;
};

TAILQ_HEAD(tailhead, entry);

int
main(void)
{
    struct entry *n1, *n2, *n3, *np;
    struct tailhead head;
    int i;

    TAILQ_INIT(&head);

    n1 = malloc(sizeof(struct entry));
    TAILQ_INSERT_HEAD(&head, n1, entries);

    n1 = malloc(sizeof(struct entry));
    TAILQ_INSERT_TAIL(&head, n1, entries);

    n2 = malloc(sizeof(struct entry));
    TAILQ_INSERT_AFTER(&head, n1, n2, entries);

    n3 = malloc(sizeof(struct entry));
    TAILQ_INSERT_BEFORE(n2, n3, entries);

    TAILQ_REMOVE(&head, n2, entries);
    free(n2);

    i = 0;
    TAILQ_FOREACH(np, &head, entries)
	    np->data = i++;

    TAILQ_FOREACH_REVERSE(np, &head, tailhead, entries)
	    printf("%i\n", np->data);

    n1 = TAILQ_FIRST(&head);
    while (n1 != NULL) {
	    n2 = TAILQ_NEXT(n1, entries);
	    free(n1);
	    n1 = n2;
    }
    TAILQ_INIT(&head);

    exit(EXIT_SUCCESS);
}
