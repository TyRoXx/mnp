#include <stdio.h>
#include <stdlib.h>

typedef struct trie_child_entry trie_child_entry;

typedef struct trie
{
	/*a sequence of child tries which are not sorted in
	this implementation*/
	trie_child_entry *entries, *entries_end;

	/*is set to 1 if this (child) trie accepts the empty word*/
	int is_end;
}
trie;

struct trie_child_entry
{
	/*character accepted by this child connection*/
	char key;

	trie child;
};

/*constructs a valid non-ending trie with no children*/
static void construct_trie(trie *t)
{
	t->entries = t->entries_end = 0;
	t->is_end = 0;
}

/*frees the memory used by the trie and its children recursively*/
static void destroy_trie(trie *t)
{
	trie_child_entry *child;

	for (child = t->entries; child != t->entries_end; ++child)
	{
		destroy_trie(&child->child);
	}

	free(t->entries);
}

/*Returns a child connection for the given character if existant.
Otherwise, nullptr is returned.
The worst-case complexity is linear for the number of children.*/
static trie_child_entry *find_child_entry(trie const *t, char key)
{
	trie_child_entry *child;

	for (child = t->entries; child != t->entries_end; ++child)
	{
		if (child->key == key)
		{
			return child;
		}
	}

	return 0;
}

/*Modifies the trie to make it accept a given word.
If the word is already in the trie, the function returns 1.
The function returns 0 if a memory allocation fails. The trie
is not changed in that case.
The pointer pointed to by begin should point to the beginning
of the word before the call. After a successful call the pointer
points after the end of the word or after the comma after the
word. The end of the word should be indicated by the caller with
a zero-character or a comma.
When the function returns 0 the *begin pointer has an unspecified
value.*/
static int insert_word(trie *t, char const **begin)
{
	if (**begin == '\0')
	{
		t->is_end = 1;
		return 1;
	}
	else if (**begin == ',')
	{
		++(*begin);
		t->is_end = 1;
		return 1;
	}
	else
	{
		trie_child_entry * const child = find_child_entry(t, **begin);
		if (child)
		{
			++(*begin);
			return insert_word(&child->child, begin);
		}
		else
		{
			size_t const new_entry_count = (t->entries_end - t->entries) + 1;
			trie_child_entry * const new_entries =
				realloc(t->entries, sizeof(*new_entries) * new_entry_count);

			trie_child_entry *new_entry;

			if (!new_entries)
			{
				return 0;
			}

			t->entries = new_entries;
			t->entries_end = new_entries + new_entry_count;

			new_entry = t->entries_end - 1;
			new_entry->key = **begin;
			construct_trie(&new_entry->child);

			++(*begin);
			return insert_word(&new_entry->child, begin);
		}
	}
}

/*Inserts all comma separated words into the trie.
Returns 0 if a memory allocation fails. In that case any
subset of the words may have been inserted into the tree.*/
static int insert_words(trie *t, char const *words)
{
	while (*words != '\0')
	{
		if (!insert_word(t, &words))
		{
			return 0;
		}
	}

	return 1;
}

/*Returns whether the word is accepted by the trie.*/
static int search_word(trie const *t, char const *word)
{
	trie_child_entry *child;

	if (*word == '\0')
	{
		return t->is_end;
	}

	child = find_child_entry(t, *word);

	if (child)
	{
		return search_word(&child->child, word + 1);
	}
	else
	{
		return 0;
	}
}

/*Writes a given number of tab characters to the file.*/
static void print_indentation(size_t indentation, FILE *out)
{
	while (indentation--)
	{
		fputs("\t", out);
	}
}

/*Recursively prints the trie in a human-readable format to the file.*/
static void print_trie(trie const *t, FILE *out, size_t indentation)
{
	trie_child_entry *child;

	if (t->is_end)
	{
		fputs("[end]", out);
	}

	fputs("\n", out);

	++indentation;

	for (child = t->entries; child != t->entries_end; ++child)
	{
		print_indentation(indentation, out);
		fprintf(out, "%c ", child->key);
		print_trie(&child->child, out, indentation);
	}
}

/*Opens a file with the specified file name and prints the trie in
a human-readable format into it. Returns whether the file could be
successfully opened.*/
static int print_trie_to_file(trie const *t, char const *file_name)
{
	FILE * const out = fopen(file_name, "w");
	if (!out)
	{
		return 0;
	}
	print_trie(t, out, 0);
	fclose(out);
	return 1;
}

/*Construcs a trie from a comma-separated list of words and prints it
to a specified file. Tests for expected and unexpected words and prints
to stdout accordingly.*/
static void test_trie(
	char const *test_name,
	char const *inserted,
	char const * const *positive,
	char const * const *negative)
{
	size_t i;
	trie t;

	printf("Test: %s\n", test_name);

	construct_trie(&t);

	if (!insert_words(&t, inserted))
	{
		printf("insert_words failed\n");
		return;
	}

	print_trie_to_file(&t, test_name);

	for (i = 0; positive[i]; ++i)
	{
		if (search_word(&t, positive[i]) == 0)
		{
			printf("word \"%s\" was not found\n", positive[i]);
		}
	}

	for (i = 0; negative[i]; ++i)
	{
		if (search_word(&t, negative[i]) == 1)
		{
			printf("word \"%s\" was incorrectly found\n", negative[i]);
		}
	}

	destroy_trie(&t);
}

static char const * const big_input = 
"takeoffs,rifling,subroutine,plead,deployments,seats,clothing,certificate,works,helmet,governors,states,"
"tabulations,manifests,algorithm,explanations,son,progress,outline,chin,summary,junction,food,curvatures,"
"privates,broadcast,fund,curtains,capes,digits,laundry,centers,gaskets,compliance,cameras,machinery,"
"surfaces,screwdriver,others,provision,surprises,helmsman,attorney,foot,swabs,inceptions,bowl,tailors,"
"quarterdecks,positions,sailor,retrieval,doorknob,perforators,breaks,traps,effectiveness,notice,budget,"
"warning,profit,acts,setups,secrets,segments,professions,curvature,limp,rings,lens,parcels,turnarounds,"
"superstructures,debts,thyristor,burn,maples,linkage,illustration,specification,lapses,designations,till,"
"allegations,nulls,platter,inclination,lessons,signals,amounts,mark,passbook,buildings,sips,military,"
"profiles,conventions,object,array,nomenclatures,diameter,features,boats,equations,base,permits,story,"
"accountability,missiles,bands,mustard,teeth,disks,site,weathers,washes,model,dependents,gangways,voice,"
"integers,reproduction,recombinations,badges,noun,mathematics,operators,morphine,skip,seal,terms,cruises,"
"plexiglass,drunkeness,head,slash,byte,laughs,gravel,shadows,door,gland,aptitudes,wrap,instance,cushions,"
"misfits,managers,closure,junk,sentry,closures,chairwoman,fake,september,change,fuses,cups,journals,cuff,"
"round,lockers,piston,stretchers,remainders,abilities,kiloliters,rocket,summaries,sessions,grinders,sponsor,"
"section,crewmembers,pay,jackets,meeting,hats,representative,wastes,diode,hitch,correlation,wholesales,"
"ideals,prop,cords,mug,swell,commands,displacements,glow,keywords,bail,helms,centimeters,releases,beacons,"
"indicator,ohm,delimiters,bore,handler,punishments,college,moisture,pleasure,subtotal,boxcars,skirt,freezes,"
"business,types,laundries,dependence,leak,evidence,blocks,dynamics,existence,desertions,thread,billet,"
"abuses,pace,knee,summers,equipment,draft,spike,dimensions,tries,evaluation,skills,gears,ignitions,sod,"
"accommodation,clubs,contrasts,repair,leads,mineral,breast,moneys,west,seasoning,alignment,harm,completion,"
"enemy,drunk,ammonia,augmentation,rose,hygiene,radiators,veteran,spacer,ammunition,adherence,answer,"
"complement,reservoirs,jig,architecture,bricks,abrasive,powders,semicolons,coals,frigate,span,plating,"
"blindfolds,fires,carburetors,feet,components,accidents,recipient,lifts,problems,goggles,ears,spindle,"
"troubleshooters,term,cylinders,meals,paygrade,buy,silences,south,filler,stress,bunch,neutron,cheeses,"
"hunte,hunde,hundehuette,hundehaus,huntehaus";

static char const * const big_positive[] = {
"takeoffs","tabulations","privates","broadcast","surfaces","screwdriver",
"quarterdecks","positions","warning","profit","superstructures","debts","thyristor","allegations",
"profiles","conventions","object","array","nomenclatures","diameter","features","boats","equations",
"base","permits","story","hunte","huntehaus",0};

static char const * const big_negative[] = {
"takeoff","tabullations","private","broadcst","surface","screwriver",
"quarterdeckss","position","warnings","proit","sperstructures","dets","thristor","alegations",
"profile","convention","objects","arrayy","nomenclatres","diameer","fetures","bots","equtions",
"yoda","permit","storryy","hunt","hundehuet",0};

static void test_big(void)
{
	test_trie("big_trie.txt", big_input, big_positive, big_negative);
}

static char const * const empty_input = "";
static char const * const empty_positive[] = {0};
static char const * const * const empty_negative = big_positive;
static void test_empty(void)
{
	test_trie("empty_trie.txt", empty_input, empty_positive, empty_negative);
}

static char const * const small_input = "abc,abcd,ab,aa";
static char const * const small_positive[] = {"abc", "abcd", "ab", "aa", 0};
static char const * const small_negative[] = {"", "a", 0};
static void test_small(void)
{
	test_trie("small_trie.txt", small_input, small_positive, small_negative);
}

int main(void)
{
	test_empty();
	test_small();
	test_big();
	return 0;
}
