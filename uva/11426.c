#include <stdio.h>
#include <assert.h>

int fast_exp(int b, int n)
{
  int res = 1;
  int x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res *= x;
    } else {
      n >>= 1;
      x *= x;
    }
  }

  return res;
}

int eulerphi[4000001];

void compute_phi(void)
{
  long long n, p;
  long long t;
  char factors[4000001];
  char prime[4000001];

  for (n = 1; n <= 4000000; n++) {
    eulerphi[n] = 1;
    prime[n] = 1;
  }

  for (p = 2; p <= 4000000; p++) {
    if (!prime[p]) continue;
    factors[p] = 1;
    for (n = 2*p; n <= 4000000; n += p) {
      prime[n] = 0;
      factors[n] = 1;
    }

    for (t = p*p; t <= 4000000; t *= p) {
      for (n = t; n <= 4000000; n += t) {
        factors[n]++;
      }
    }
    
    for (n = p; n <= 4000000; n += p) {
      eulerphi[n] *= fast_exp(p, factors[n]-1) * (p-1);
    }
  }

}

/* G(N) = \sum_{i=1}^{N-1} \sum_{j=i+1}^N \gcd(i,j)
        = \sum_{i=1}^{N-2} \sum_{j=i+1}^N \gcd(i,j) + gcd(N-1,N)
        = \sum_{i=1}^{N-2} \sum_{j=i+1}^N \gcd(i,j) + gcd(N-1,N)
        = \sum_{i=1}^{N-2} (\sum_{j=i+1}^{N-1} \gcd(i,j) + gcd(i,N)) + 
          gcd(N-1,N)
        = G(N-1) + \sum_{i=1}^{N-1} gcd(i, N)
   
   Now, \sum_{i=1}^{N-1} gcd(i, N) = gcd(1,N) + gcd(2,N) + ... + gcd(N-1,N).
   
   The number of gcd(i,N) = 1 is phi(N)
   The number of gcd(i,N) = 2 is phi(N/2) if N is even, otherwise 0
   etc.
   
   so we want to add phi(N) + 2*phi(N/2) + 3*phi(N/3) + ... + 
                    (N-1)*phi(N/(N-1))
   
   but only include the terms that where N/k is an integer.  So we
   can use a sieve.

   To compute G(n), we want to add up the sum above from N = 2..n.

   We also store the values of G(n) where n is a multiple of 5000 to
   speed up the sum (so we start adding from G(n)).

*/

long long table[801] = {
  0,
  61567426LL,
  267252140LL,
  628964502LL,
  1153104356LL,
  1843992862LL,
  2705402000LL,
  3739785714LL,
  4949380400LL,
  6336834562LL,
  7902706060LL,
  9650749814LL,
  11579839364LL,
  13693372650LL,
  15990684880LL,
  18474334042LL,
  21144774632LL,
  24004044974LL,
  27053440504LL,
  30289480718LL,
  33717147452LL,
  37338433862LL,
  41149811952LL,
  45152987254LL,
  49351875552LL,
  53743934578LL,
  58331505692LL,
  63113809962LL,
  68091551940LL,
  73267500802LL,
  78638126632LL,
  84204996658LL,
  89974755012LL,
  95940749502LL,
  102103077648LL,
  108468170978LL,
  115035496392LL,
  121797255894LL,
  128763227796LL,
  135932676974LL,
  143295493160LL,
  150864216294LL,
  158640813740LL,
  166610146134LL,
  174791094492LL,
  183174262546LL,
  191758270892LL,
  200544717538LL,
  209538240812LL,
  218740057710LL,
  228142848072LL,
  237748281314LL,
  247561321332LL,
  257583836746LL,
  267812878760LL,
  278242942838LL,
  288879531360LL,
  299727608170LL,
  310781545804LL,
  322043100778LL,
  333511480528LL,
  345189454874LL,
  357068727080LL,
  369166446742LL,
  381467360396LL,
  393978020410LL,
  406702643880LL,
  419632190034LL,
  432767947496LL,
  446123911286LL,
  459680915348LL,
  473447888806LL,
  487441332520LL,
  501622554150LL,
  516033574108LL,
  530644301494LL,
  545472423832LL,
  560512241470LL,
  575765704544LL,
  591219912290LL,
  606891759716LL,
  622787477466LL,
  638880446232LL,
  655191082254LL,
  671727655276LL,
  688454513106LL,
  705399766804LL,
  722573071202LL,
  739952290288LL,
  757543611790LL,
  775358473308LL,
  793370346962LL,
  811608972420LL,
  830050403994LL,
  848717604804LL,
  867598809314LL,
  886697788928LL,
  905997056574LL,
  925546174408LL,
  945274395798LL,
  965233338244LL,
  985401001966LL,
  1005786940752LL,
  1026393263518LL,
  1047213707192LL,
  1068260624510LL,
  1089509473520LL,
  1110972716518LL,
  1132671017816LL,
  1154577359946LL,
  1176696679804LL,
  1199026183410LL,
  1221582047488LL,
  1244364060574LL,
  1267358766560LL,
  1290556658674LL,
  1313994662876LL,
  1337647693478LL,
  1361499155988LL,
  1385583104566LL,
  1409876279644LL,
  1434411998850LL,
  1459143730936LL,
  1484093772490LL,
  1509266214348LL,
  1534660377982LL,
  1560284098996LL,
  1586098651270LL,
  1612174439412LL,
  1638439269362LL,
  1664930390148LL,
  1691641193114LL,
  1718574572016LL,
  1745729371714LL,
  1773105885424LL,
  1800699869330LL,
  1828500544464LL,
  1856542650990LL,
  1884805640872LL,
  1913252213506LL,
  1941959023344LL,
  1970874902238LL,
  2000011508800LL,
  2029369995498LL,
  2058955021388LL,
  2088747721714LL,
  2118770871316LL,
  2149033510850LL,
  2179488557688LL,
  2210182384174LL,
  2241093103756LL,
  2272205823858LL,
  2303576593788LL,
  2335146707754LL,
  2366946080036LL,
  2398960788634LL,
  2431221149160LL,
  2463681964954LL,
  2496358920824LL,
  2529283668750LL,
  2562408495936LL,
  2595765459742LL,
  2629395318484LL,
  2663157833386LL,
  2697184911848LL,
  2731448841922LL,
  2765895467488LL,
  2800594839402LL,
  2835534141008LL,
  2870680180814LL,
  2906028891364LL,
  2941644891534LL,
  2977438251596LL,
  3013491428002LL,
  3049754376184LL,
  3086218617650LL,
  3122957677188LL,
  3159882813426LL,
  3197052147164LL,
  3234463853178LL,
  3272069791044LL,
  3309875368010LL,
  3347941153580LL,
  3386246540118LL,
  3424758945952LL,
  3463451140290LL,
  3502435447748LL,
  3541652222130LL,
  3581028613496LL,
  3620683039154LL,
  3660536781832LL,
  3700639740402LL,
  3740960181016LL,
  3781486060782LL,
  3822240416496LL,
  3863247425370LL,
  3904478407208LL,
  3945919020602LL,
  3987589577744LL,
  4029473242170LL,
  4071628673912LL,
  4113955027866LL,
  4156520027692LL,
  4199322505898LL,
  4242348602712LL,
  4285596492030LL,
  4329075520176LL,
  4372809112314LL,
  4416743050360LL,
  4460909337530LL,
  4505287265376LL,
  4549900499290LL,
  4594749434596LL,
  4639798639626LL,
  4685109426452LL,
  4730616504690LL,
  4776413888548LL,
  4822368168878LL,
  4868620074088LL,
  4915001393542LL,
  4961694745032LL,
  5008575174602LL,
  5055705572920LL,
  5103041259926LL,
  5150645738564LL,
  5198443407422LL,
  5246455067164LL,
  5294700693750LL,
  5343210380080LL,
  5391880472926LL,
  5440882658088LL,
  5490065402218LL,
  5539440828184LL,
  5589101373906LL,
  5638985735696LL,
  5689003800074LL,
  5739344476692LL,
  5789870357190LL,
  5840675795980LL,
  5891643486946LL,
  5942886226516LL,
  5994339204410LL,
  6046111619224LL,
  6097984538406LL,
  6150128522232LL,
  6202509807842LL,
  6255130573244LL,
  6307950543014LL,
  6361022611556LL,
  6414319269018LL,
  6467836788284LL,
  6521591235526LL,
  6575622325244LL,
  6629795639506LL,
  6684232597832LL,
  6738928530770LL,
  6793835688344LL,
  6848954069634LL,
  6904329934816LL,
  6959949674938LL,
  7015772842708LL,
  7071822940030LL,
  7128115715784LL,
  7184618638282LL,
  7241395512932LL,
  7298352572966LL,
  7355608782324LL,
  7413038700010LL,
  7470714610204LL,
  7528561821034LL,
  7586751706808LL,
  7645076107326LL,
  7703704117740LL,
  7762541364262LL,
  7821590604148LL,
  7880867852814LL,
  7940429551516LL,
  8000119895710LL,
  8060085119820LL,
  8120334911914LL,
  8180784306640LL,
  8241434949494LL,
  8302356397812LL,
  8363506590298LL,
  8424860557144LL,
  8486465905030LL,
  8548321342304LL,
  8610383012026LL,
  8672694894712LL,
  8735215821098LL,
  8797973470756LL,
  8860963657510LL,
  8924188697236LL,
  8987638218294LL,
  9051392383916LL,
  9115331752918LL,
  9179403396132LL,
  9243832647446LL,
  9308466437596LL,
  9373362693118LL,
  9438396116332LL,
  9503703232298LL,
  9569215453092LL,
  9635032310602LL,
  9701063898388LL,
  9767301501890LL,
  9833794472764LL,
  9900468570978LL,
  9967439562416LL,
  10034644876398LL,
  10102030304488LL,
  10169733492970LL,
  10237604716276LL,
  10305729915442LL,
  10374010494688LL,
  10442610495778LL,
  10511410332924LL,
  10580472483518LL,
  10649744925620LL,
  10719298653254LL,
  10788976526912LL,
  10858975066826LL,
  10929195671296LL,
  10999669227890LL,
  11070408254472LL,
  11141249266306LL,
  11212378849900LL,
  11283793320014LL,
  11355363867932LL,
  11427236110322LL,
  11499368064896LL,
  11571588251258LL,
  11644164487992LL,
  11716955055638LL,
  11790018442064LL,
  11863249633670LL,
  11936727772668LL,
  12010483182586LL,
  12084434338652LL,
  12158618377858LL,
  12233015302656LL,
  12307727531582LL,
  12382616484428LL,
  12457763305606LL,
  12533040486124LL,
  12608681275370LL,
  12684518857920LL,
  12760516792014LL,
  12836893627348LL,
  12913434040454LL,
  12990142569372LL,
  13067286095818LL,
  13144463826564LL,
  13221871557006LL,
  13299603959520LL,
  13377520851650LL,
  13455746060856LL,
  13534235065010LL,
  13612818929968LL,
  13691699322934LL,
  13770820424944LL,
  13850304598290LL,
  13929757598020LL,
  14009659318386LL,
  14089659092760LL,
  14169996197930LL,
  14250509752656LL,
  14331270958058LL,
  14412287436820LL,
  14493527790854LL,
  14574966575144LL,
  14656742497910LL,
  14738662138588LL,
  14820798273238LL,
  14903308660008LL,
  14985880612786LL,
  15068804995844LL,
  15151986088442LL,
  15235340794124LL,
  15318921896302LL,
  15402739398648LL,
  15486796938098LL,
  15571164064224LL,
  15655697246142LL,
  15740518724376LL,
  15825520274210LL,
  15910704516488LL,
  15996250096194LL,
  16081940475820LL,
  16167893290830LL,
  16254121264420LL,
  16340564265318LL,
  16427266109860LL,
  16514120781050LL,
  16601248750088LL,
  16688652151354LL,
  16776311525396LL,
  16864106429022LL,
  16952206551536LL,
  17040592289458LL,
  17129192436684LL,
  17217971308946LL,
  17306986618280LL,
  17396253371170LL,
  17485746878764LL,
  17575535888098LL,
  17665499079992LL,
  17755719126510LL,
  17846210035660LL,
  17936909474650LL,
  18027813184656LL,
  18119019896878LL,
  18210436964540LL,
  18302086620886LL,
  18393982266684LL,
  18486056936906LL,
  18578490344992LL,
  18671078140574LL,
  18763937517204LL,
  18856904585842LL,
  18950295276704LL,
  19043716281538LL,
  19137579011380LL,
  19231671167310LL,
  19325929586576LL,
  19420380717002LL,
  19515123241388LL,
  19610141135378LL,
  19705328573864LL,
  19800747194574LL,
  19896426512076LL,
  19992415434178LL,
  20088548151552LL,
  20184907762370LL,
  20281593074596LL,
  20378453850638LL,
  20475645532124LL,
  20572882984714LL,
  20670570514044LL,
  20768382145350LL,
  20866477267404LL,
  20964808693870LL,
  21063292495968LL,
  21162069275398LL,
  21261143112324LL,
  21360484393038LL,
  21459904678548LL,
  21559629964854LL,
  21659653475244LL,
  21759801383254LL,
  21860351876044LL,
  21960976460754LL,
  22061896610856LL,
  22163078366554LL,
  22264506303064LL,
  22366162955946LL,
  22468061391620LL,
  22570180965222LL,
  22672478516528LL,
  22775095548298LL,
  22878084619388LL,
  22981029421394LL,
  23084424241012LL,
  23187988638758LL,
  23291772137276LL,
  23395842250266LL,
  23500116546912LL,
  23604651349094LL,
  23709474339924LL,
  23814429128998LL,
  23919566791848LL,
  24025064029898LL,
  24130749139580LL,
  24236751362506LL,
  24342889010480LL,
  24449361256094LL,
  24556069807824LL,
  24662979434754LL,
  24770072869436LL,
  24877512249138LL,
  24985113854516LL,
  25093069289342LL,
  25201109820736LL,
  25309540762682LL,
  25418198272004LL,
  25526841066822LL,
  25636096947860LL,
  25745248901882LL,
  25854828388804LL,
  25964661854486LL,
  26074724986624LL,
  26184870408838LL,
  26295476926424LL,
  26406188403890LL,
  26517187026576LL,
  26628426349510LL,
  26739881312312LL,
  26851576075626LL,
  26963506826620LL,
  27075734100454LL,
  27188106028636LL,
  27300850896930LL,
  27413752705684LL,
  27526938888570LL,
  27640360188540LL,
  27753920249330LL,
  27867810470192LL,
  27981988935894LL,
  28096229430664LL,
  28210844847266LL,
  28325710779484LL,
  28440823106986LL,
  28556144442064LL,
  28671753696294LL,
  28787442622908LL,
  28903473202690LL,
  29019753919772LL,
  29136276524518LL,
  29253078112856LL,
  29370114662758LL,
  29487315420012LL,
  29604909209466LL,
  29722538930020LL,
  29840419263422LL,
  29958646397988LL,
  30077141647346LL,
  30195751581680LL,
  30314827121350LL,
  30433924892084LL,
  30553340752294LL,
  30672980159836LL,
  30792872460286LL,
  30913148842520LL,
  31033419757050LL,
  31154146673452LL,
  31274932061990LL,
  31396080399188LL,
  31517425176346LL,
  31638930996028LL,
  31760725925042LL,
  31882864156020LL,
  32005105295110LL,
  32127678718524LL,
  32250430071670LL,
  32373521935136LL,
  32496893351438LL,
  32620323731264LL,
  32744027774050LL,
  32868140231780LL,
  32992309924698LL,
  33116764940592LL,
  33241473474594LL,
  33366584798836LL,
  33491643431030LL,
  33617029093524LL,
  33742713691394LL,
  33868706128816LL,
  33994922040054LL,
  34121354785816LL,
  34247973184898LL,
  34374915857804LL,
  34502138453450LL,
  34629438539844LL,
  34757050643946LL,
  34884912729548LL,
  35013064398298LL,
  35141405349660LL,
  35270006548058LL,
  35398818107608LL,
  35527906349346LL,
  35657248028932LL,
  35786813719374LL,
  35916617219208LL,
  36046678603738LL,
  36176970097736LL,
  36307404694374LL,
  36438317808508LL,
  36569268584434LL,
  36700605439880LL,
  36832079303494LL,
  36963741968940LL,
  37095720918762LL,
  37228004970588LL,
  37360490156470LL,
  37493198940024LL,
  37626243029986LL,
  37759317944640LL,
  37892780725498LL,
  38026548852040LL,
  38160488118178LL,
  38294676030948LL,
  38429066765310LL,
  38563607279420LL,
  38698575542014LL,
  38833724952400LL,
  38969078077486LL,
  39104819444700LL,
  39240661894154LL,
  39376911134012LL,
  39513142389242LL,
  39649802308964LL,
  39786599721026LL,
  39923716116652LL,
  40061004429322LL,
  40198477341504LL,
  40336480286282LL,
  40474463803112LL,
  40612786197074LL,
  40751356585540LL,
  40890092683190LL,
  41029106649872LL,
  41168381378954LL,
  41307938654340LL,
  41447668863422LL,
  41587692565068LL,
  41728050197754LL,
  41868535917160LL,
  42009081335930LL,
  42150189489388LL,
  42291401108942LL,
  42432895660568LL,
  42574623466918LL,
  42716633425888LL,
  42858737496482LL,
  43001279106944LL,
  43143944914298LL,
  43286898682516LL,
  43430049485166LL,
  43573457784220LL,
  43717092270554LL,
  43861024454928LL,
  44005066279458LL,
  44149523060500LL,
  44294170667434LL,
  44439065742544LL,
  44584178948642LL,
  44729557068712LL,
  44875231394534LL,
  45020995791728LL,
  45167076155950LL,
  45313465662012LL,
  45460102276690LL,
  45606880866564LL,
  45753905810662LL,
  45901342539084LL,
  46048828822634LL,
  46196696784356LL,
  46344645151502LL,
  46493158376984LL,
  46641751159566LL,
  46790410352944LL,
  46939438687490LL,
  47088665220444LL,
  47238167262966LL,
  47387974204080LL,
  47538002440722LL,
  47688160739668LL,
  47838682778118LL,
  47989434222784LL,
  48140370450406LL,
  48291795492436LL,
  48443064283714LL,
  48594792933300LL,
  48746875576610LL,
  48898984864132LL,
  49051540863054LL,
  49204202580184LL,
  49357235978610LL,
  49510364806968LL,
  49663744823542LL,
  49817426502088LL,
  49971337215678LL,
  50125574968460LL,
  50279843381646LL,
  50434599419128LL,
  50589487667594LL,
  50744631000568LL,
  50900075485062LL,
  51055671461620LL,
  51211520190474LL,
  51367671447196LL,
  51524025926302LL,
  51680759478756LL,
  51837512444350LL,
  51994705903052LL,
  52151900982958LL,
  52309817680528LL,
  52467314625194LL,
  52625440856712LL,
  52783780533786LL,
  52942505977328LL,
  53101199396810LL,
  53260432376732LL,
  53419714278742LL,
  53579045173568LL,
  53738885864490LL,
  53899008167308LL,
  54059235347414LL,
  54219815463120LL,
  54380731481622LL,
  54541616410124LL,
  54702949398998LL,
  54864746987528LL,
  55026202256162LL,
  55188285333256LL,
  55350512832126LL,
  55512865091996LL,
  55675725873566LL,
  55838712119468LL,
  56001912892806LL,
  56165417463048LL,
  56329170521966LL,
  56493223063772LL,
  56657372815134LL,
  56821979054976LL,
  56986619105578LL,
  57151611845424LL,
  57316752845526LL,
  57482169144404LL,
  57647871726278LL,
  57813814076752LL,
  57980024415922LL,
  58146608609792LL,
  58313087694966LL,
  58480006721856LL,
  58647208032422LL,
  58814873758864LL,
  58982275493310LL,
  59150204835768LL,
  59318501045962LL,
  59486832331448LL,
  59655382558954LL,
  59824282066660LL,
  59993343166710LL,
  60162841878792LL,
  60332595396862LL,
  60502343890184LL,
  60672374121790LL,
  60842917708884LL,
  61013533573286LL,
  61184240175908LL,
  61355460347238LL,
  61526805673420LL,
  61698349464018LL,
  61870190669048LL,
  62042415079962LL,
  62214600315216LL,
  62387227599166LL,
  62560144118168LL,
  62733237337502LL,
  62906406730740LL,
  63080153323822LL,
  63253882361052LL,
  63427930395298LL,
  63602270503376LL,
  63776858622562LL,
  63951740236584LL,
  64126798785882LL,
  64302023046148LL,
  64477582336854LL,
  64653343222432LL,
  64829392353070LL,
  65005586534552LL,
  65182204026810LL,
  65358993948384LL,
  65536068343826LL,
  65713251973108LL,
  65890800716054LL,
  66068605247256LL,
  66246556528474LL,
  66424830014708LL,
  66603314586634LL,
  66782021465940LL,
  66961050878298LL,
  67140369842608LL,
  67319849103662LL,
  67499596224456LL,
  67679613697366LL,
  67859808872972LL,
  68040305317822LL,
  68220983333848LL,
  68402094056586LL,
  68583309383644LL,
  68764687451986LL,
  68946462419600LL,
  69128343461046LL,
  69310544155000LL,
  69492954957190LL,
  69675610807812LL,
  69858671761634LL,
  70041850544356LL,
  70225299904910LL,
  70409164725680LL,
  70593216389402LL,
  70777152095004LL,
  70961598198930LL,
  71146285802016LL,
  71331138204598LL,
  71516583828500LL,
  71701792299278LL,
  71887733425828LL
};

long long G(int n)
{
  long long ans = table[n/5000];
  int N, k, start, t;

  for (k = 1; k <= n/2; k++) {
    start = n/5000*5000+1;   /* first n value that needs computed */
    if ((t = start % k)) {
      start += k-t;
    }
    if (start < 2*k) {
      start += k;
    }
    for (N = start; N <= n; N += k) {
      ans += k*eulerphi[N/k];
    }
  }

  return ans;
}

int main(void)
{

  int N;

  compute_phi();

  while (scanf("%d", &N) == 1 && N > 0) {
    printf("%lld\n", G(N));
  }

  return 0;
}
