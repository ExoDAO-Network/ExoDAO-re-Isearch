/* $Id: cql2xcql.c 77 2005-07-11 19:55:55Z warnock $
   Copyright (C) 1995-2005, Index Data ApS
   Index Data Aps

This file is part of the YAZ toolkit.

See the file LICENSE.
*/

#include <stdio.h>
#include <stdlib.h>

#include <yaz/cql.h>
/*#include <yaz/options.h>*/

int main(int argc, char **argv)
{
    CQL_parser cp;
    int r = 0;
    const char *fname = 0;
    int iterations = 1;
    int ret;
    char *arg;

    /*
    while ((ret = options("n:", argv, argc, &arg)) != -2)
    {
        switch (ret)
        {
        case 0:
	    fname = arg;
            break;
	case 'n':
	    iterations = atoi(arg);
	    break;
	}
    }
    */
    cp = cql_parser_create();
    if (fname)
    {
	int i;
	for (i = 0; i<iterations; i++)
	    r = cql_parser_string(cp, fname);
    }
    else
        r = cql_parser_stdio(cp, stdin);
    if (r)
        fprintf (stderr, "Syntax error\n");
    else
        cql_to_xml_stdio(cql_parser_result(cp), stdout);
    cql_parser_destroy(cp);
    return 0;
}
