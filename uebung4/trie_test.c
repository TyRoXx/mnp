#include <stdio.h>
#include <stdlib.h>


typedef struct trie_child_entry trie_child_entry;

typedef struct trie
{
	trie_child_entry *entries, *entries_end;
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

/* inserts all comma seperated words into the trie */
static void insert_words(trie *t, char const * words)
{
}

/* searches a single word in the trie
   return 1 if the word is found, 0 otherwise
 */
static int search_word(trie const *t, char const *word)
{
	return 0;
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
	insert_words(&t, input_string);

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
