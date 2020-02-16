/**
 * @author      : alpha (alpha@mascot)
 * @created     : Sunday Feb 16, 2020 23:26:38 HKT
 */

#include <stdio.h>
#include <string.h>

typedef int (*pair_handler_t)(char *key, char *value, void *data);
struct option {
	char *buffer;
	const char *delimiter0;
	const char *delimiter1;
	const char *delimiter2;
	pair_handler_t handler;
	void *data;
};

int callback_handler(char *key, char *value, void *data)
{
	printf("key='%s', value='%s'\n", key, value);
}

static int process_pair(struct option *opt, char *key, char *value)
{
	return opt->handler(key, value, opt->data);
}

static int parse(struct option *opt)
{
	char *pair = NULL;
	char *key = NULL;
	char *value = NULL;
	char *buf = opt->buffer;
	char *buf_next = NULL;
	char *pair_next = NULL;

	printf("parse:'%s'\n", buf);
	while ((pair = strtok_r(buf, opt->delimiter0, &buf_next)) != NULL) {
		buf = NULL;
		printf("parse pair:'%s'\n", pair);
		char *left = strtok_r(pair, opt->delimiter1, &pair_next);
		if (left == NULL) {
			continue;
		}
		if (left == pair) {
			key = left;
			pair = NULL;
			printf("get key:'%s'\n", key);
			value = strtok_r(pair, opt->delimiter1, &pair_next);
			printf("get value:'%s'\n", value);
		} else {
			value = left;
			printf("get value:'%s'\n", value);
		}

		if (opt->delimiter2 != NULL) {
			char *tmp = NULL;
			key = strtok_r(key, opt->delimiter2, &tmp);
			value = strtok_r(value, opt->delimiter2, &tmp);
		}
		process_pair(opt, key, value);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char buffer[] = "a=1, b =2, c= 3, d=4 , e = 5 ,f=, g, =7,=,,,";
	struct option parse_opt = {
		.buffer = buffer,
		.delimiter0 = ",",
		.delimiter1 = "=",
		.delimiter2 = " ",
		.handler = callback_handler,
		.data = NULL,
	};

	parse(&parse_opt);

	return 0;
}
