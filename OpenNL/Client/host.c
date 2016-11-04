#include "../OpenNL/inc/nl.h"
#pragma comment(lib,"../Debug/OpenNL.lib")


#include <stdio.h>


int main(int argc, char *argv[])
{
	nlInit(2,0);

	if (argc < 2)
	{
		printf("Usage :%s name | IP", argv[0]);
		exit(1);
	}

	PNLHost he;
	char                    **alias;
	argv++;
	for (; *argv != NULL; argv++)
	{
		he = nlHsName(*argv);
		printf("address information of host %s:\n", *argv);


		if (he == NULL)
		{
			printf("no address information of %s\n", *argv);
			continue;
		}

		printf("Officaial host name: %s\n", he->h_name);
		printf("name aliases:");
		for (alias = he->h_aliases; *alias != NULL; alias++)
			printf("%s\n", *alias);
		printf("\nIP addresses: ");
		for (alias = he->h_addr_list; *alias != NULL; alias++)
			printf("%s\n", inet_ntoa(*(struct in_addr *)(*alias)));
	}

	nlUnInit();
}