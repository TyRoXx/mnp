#include <stdio.h>
#include <stdlib.h>


typedef struct trie_child_entry trie_child_entry;

typedef struct trie
{
	trie_child_entry *entries, *entries_end;
	int is_end;
}
trie;

struct trie_child_entry
{
	char key;
	trie child;
};

/* constructs a initial trie node */
static void construct_trie(trie *t)
{
	t->entries = t->entries_end = 0;
	t->is_end = 0;
}

static void destroy_trie(trie *t)
{
	trie_child_entry *child;

	for (child = t->entries; child != t->entries_end; ++child)
	{
		destroy_trie(&child->child);
	}

	free(t->entries);
}

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
			return 1;
		}
	}
}

/* inserts all comma seperated words into the trie */
static int insert_words(trie *t, char const * words)
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

/* searches a single word in the trie
   return 1 if the word is found, 0 otherwise
 */
static int search_word(trie const *t, char const *word)
{
	trie_child_entry *child;

	if (*word == '\0')
	{
		return
			(t->is_end) ||
			(t->entries == t->entries_end);
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

static char const * const input_string = 
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

static char const * const positive_test[] = {
"takeoffs","tabulations","privates","broadcast","surfaces","screwdriver",
"quarterdecks","positions","warning","profit","superstructures","debts","thyristor","allegations",
"profiles","conventions","object","array","nomenclatures","diameter","features","boats","equations",
"base","permits","story","hunte","huntehaus",0};

static char const * const negative_test[] = {
"takeoff","tabullations","private","broadcst","surface","screwriver",
"quarterdeckss","position","warnings","proit","sperstructures","dets","thristor","alegations",
"profile","convention","objects","arrayy","nomenclatres","diameer","fetures","bots","equtions",
"yoda","permit","storryy","hunt","hundehuet",0};

int main(void)
{
	trie t;
	size_t i;

	construct_trie(&t);
	if (!insert_words(&t, input_string))
	{
		printf("insert_words failed\n");
		return 1;
	}

	for (i = 0; positive_test[i]; ++i)
	{
		if (search_word(&t, positive_test[i]) == 0)
		{
			printf("word \"%s\" was not found\n", positive_test[i]);
		}
	}

	for (i = 0; negative_test[i]; ++i)
	{
		if (search_word(&t, negative_test[i]) == 1)
		{
			printf("word \"%s\" was incorrectly found\n", negative_test[i]);
		}
	}

	destroy_trie(&t);
	return 0;
}
