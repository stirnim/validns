/*
 * Part of DNS zone file validator `validns`.
 *
 * Copyright 2011, Anton Berezin <tobez@tobez.org>
 * Modified BSD license.
 * (See LICENSE file in the distribution.)
 *
 */
#include "common.h"
#include "rr.h"

#include <arpa/inet.h>

static struct rr *aaaa_parse(char *name, long ttl, int type, char *s)
{
	struct rr_aaaa *rr = getmem(sizeof(*rr));

	if (extract_ipv6(&s, "IPv6 address", &rr->address) <= 0)
		return NULL;
	if (*s) {
		return bitch("garbage after valid AAAA data");
	}

	return store_record(type, name, ttl, rr);
}

static char* aaaa_human(struct rr *rrv)
{
    struct rr_aaaa *rr = (struct rr_aaaa *)rrv;
    char s[1024];

	if (inet_ntop(AF_INET6, &rr->address, s, 1024))
		return quickstrdup_temp(s);
	return "????";
}

static struct binary_data aaaa_wirerdata(struct rr *rrv)
{
    return bad_binary_data();
}

struct rr_methods aaaa_methods = { aaaa_parse, aaaa_human, aaaa_wirerdata, NULL, NULL };
