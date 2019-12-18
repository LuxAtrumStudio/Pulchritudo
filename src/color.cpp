#include "forma/color.hpp"

#include <string>
#include <vector>

#include "forma/math.hpp"

// static std::size_t start_cie = 390;
// static std::size_t end_cie = 830;

static float CIE_EPSILON = 0.008856f;
static float CIE_KAPPA = 903.3f;

// static float d50[] = {0.9642, 1.0000, 0.8251};
// static float d55[] = {0.9568, 1.0000, 0.9214};
static float d65[] = {0.9504, 1.0000, 1.0888};

static float x_bar[] = {
    2.952420E-03f, 3.577275E-03f, 4.332146E-03f, 5.241609E-03f, 6.333902E-03f,
    7.641137E-03f, 9.199401E-03f, 1.104869E-02f, 1.323262E-02f, 1.579791E-02f,
    1.879338E-02f, 2.226949E-02f, 2.627978E-02f, 3.087862E-02f, 3.611890E-02f,
    4.204986E-02f, 4.871256E-02f, 5.612868E-02f, 6.429866E-02f, 7.319818E-02f,
    8.277331E-02f, 9.295327E-02f, 1.037137E-01f, 1.150520E-01f, 1.269771E-01f,
    1.395127E-01f, 1.526661E-01f, 1.663054E-01f, 1.802197E-01f, 1.941448E-01f,
    2.077647E-01f, 2.207911E-01f, 2.332355E-01f, 2.452462E-01f, 2.570397E-01f,
    2.688989E-01f, 2.810677E-01f, 2.933967E-01f, 3.055933E-01f, 3.173165E-01f,
    3.281798E-01f, 3.378678E-01f, 3.465097E-01f, 3.543953E-01f, 3.618655E-01f,
    3.693084E-01f, 3.770107E-01f, 3.846850E-01f, 3.918591E-01f, 3.980192E-01f,
    4.026189E-01f, 4.052637E-01f, 4.062482E-01f, 4.060660E-01f, 4.052283E-01f,
    4.042529E-01f, 4.034808E-01f, 4.025362E-01f, 4.008675E-01f, 3.979327E-01f,
    3.932139E-01f, 3.864108E-01f, 3.779513E-01f, 3.684176E-01f, 3.583473E-01f,
    3.482214E-01f, 3.383830E-01f, 3.288309E-01f, 3.194977E-01f, 3.103345E-01f,
    3.013112E-01f, 2.923754E-01f, 2.833273E-01f, 2.739463E-01f, 2.640352E-01f,
    2.534221E-01f, 2.420135E-01f, 2.299346E-01f, 2.173617E-01f, 2.044672E-01f,
    1.914176E-01f, 1.783672E-01f, 1.654407E-01f, 1.527391E-01f, 1.403439E-01f,
    1.283167E-01f, 1.167124E-01f, 1.056121E-01f, 9.508569E-02f, 8.518206E-02f,
    7.593120E-02f, 6.733159E-02f, 5.932018E-02f, 5.184106E-02f, 4.486119E-02f,
    3.836770E-02f, 3.237296E-02f, 2.692095E-02f, 2.204070E-02f, 1.773951E-02f,
    1.400745E-02f, 1.082291E-02f, 8.168996E-03f, 6.044623E-03f, 4.462638E-03f,
    3.446810E-03f, 3.009513E-03f, 3.090744E-03f, 3.611221E-03f, 4.491435E-03f,
    5.652072E-03f, 7.035322E-03f, 8.669631E-03f, 1.060755E-02f, 1.290468E-02f,
    1.561956E-02f, 1.881640E-02f, 2.256923E-02f, 2.694456E-02f, 3.199910E-02f,
    3.778185E-02f, 4.430635E-02f, 5.146516E-02f, 5.912224E-02f, 6.714220E-02f,
    7.538941E-02f, 8.376697E-02f, 9.233581E-02f, 1.011940E-01f, 1.104362E-01f,
    1.201511E-01f, 1.303960E-01f, 1.411310E-01f, 1.522944E-01f, 1.638288E-01f,
    1.756832E-01f, 1.878114E-01f, 2.001621E-01f, 2.126822E-01f, 2.253199E-01f,
    2.380254E-01f, 2.507787E-01f, 2.636778E-01f, 2.768607E-01f, 2.904792E-01f,
    3.046991E-01f, 3.196485E-01f, 3.352447E-01f, 3.513290E-01f, 3.677148E-01f,
    3.841856E-01f, 4.005312E-01f, 4.166669E-01f, 4.325420E-01f, 4.481063E-01f,
    4.633109E-01f, 4.781440E-01f, 4.927483E-01f, 5.073315E-01f, 5.221315E-01f,
    5.374170E-01f, 5.534217E-01f, 5.701242E-01f, 5.874093E-01f, 6.051269E-01f,
    6.230892E-01f, 6.410999E-01f, 6.590659E-01f, 6.769436E-01f, 6.947143E-01f,
    7.123849E-01f, 7.299978E-01f, 7.476478E-01f, 7.654250E-01f, 7.834009E-01f,
    8.016277E-01f, 8.201041E-01f, 8.386843E-01f, 8.571936E-01f, 8.754652E-01f,
    8.933408E-01f, 9.106772E-01f, 9.273554E-01f, 9.432502E-01f, 9.582244E-01f,
    9.721304E-01f, 9.849237E-01f, 9.970067E-01f, 1.008907E+00f, 1.021163E+00f,
    1.034327E+00f, 1.048753E+00f, 1.063937E+00f, 1.079166E+00f, 1.093723E+00f,
    1.106886E+00f, 1.118106E+00f, 1.127493E+00f, 1.135317E+00f, 1.141838E+00f,
    1.147304E+00f, 1.151897E+00f, 1.155582E+00f, 1.158284E+00f, 1.159934E+00f,
    1.160477E+00f, 1.159890E+00f, 1.158259E+00f, 1.155692E+00f, 1.152293E+00f,
    1.148163E+00f, 1.143345E+00f, 1.137685E+00f, 1.130993E+00f, 1.123097E+00f,
    1.113846E+00f, 1.103152E+00f, 1.091121E+00f, 1.077902E+00f, 1.063644E+00f,
    1.048485E+00f, 1.032546E+00f, 1.015870E+00f, 9.984859E-01f, 9.804227E-01f,
    9.617111E-01f, 9.424119E-01f, 9.227049E-01f, 9.027804E-01f, 8.828123E-01f,
    8.629581E-01f, 8.432731E-01f, 8.234742E-01f, 8.032342E-01f, 7.822715E-01f,
    7.603498E-01f, 7.373739E-01f, 7.136470E-01f, 6.895336E-01f, 6.653567E-01f,
    6.413984E-01f, 6.178723E-01f, 5.948484E-01f, 5.723600E-01f, 5.504353E-01f,
    5.290979E-01f, 5.083728E-01f, 4.883006E-01f, 4.689171E-01f, 4.502486E-01f,
    4.323126E-01f, 4.150790E-01f, 3.983657E-01f, 3.819846E-01f, 3.657821E-01f,
    3.496358E-01f, 3.334937E-01f, 3.174776E-01f, 3.017298E-01f, 2.863684E-01f,
    2.714900E-01f, 2.571632E-01f, 2.434102E-01f, 2.302389E-01f, 2.176527E-01f,
    2.056507E-01f, 1.942251E-01f, 1.833530E-01f, 1.730097E-01f, 1.631716E-01f,
    1.538163E-01f, 1.449230E-01f, 1.364729E-01f, 1.284483E-01f, 1.208320E-01f,
    1.136072E-01f, 1.067579E-01f, 1.002685E-01f, 9.412394E-02f, 8.830929E-02f,
    8.281010E-02f, 7.761208E-02f, 7.270064E-02f, 6.806167E-02f, 6.368176E-02f,
    5.954815E-02f, 5.564917E-02f, 5.197543E-02f, 4.851788E-02f, 4.526737E-02f,
    4.221473E-02f, 3.934954E-02f, 3.665730E-02f, 3.412407E-02f, 3.173768E-02f,
    2.948752E-02f, 2.736717E-02f, 2.538113E-02f, 2.353356E-02f, 2.182558E-02f,
    2.025590E-02f, 1.881892E-02f, 1.749930E-02f, 1.628167E-02f, 1.515301E-02f,
    1.410230E-02f, 1.312106E-02f, 1.220509E-02f, 1.135114E-02f, 1.055593E-02f,
    9.816228E-03f, 9.128517E-03f, 8.488116E-03f, 7.890589E-03f, 7.332061E-03f,
    6.809147E-03f, 6.319204E-03f, 5.861036E-03f, 5.433624E-03f, 5.035802E-03f,
    4.666298E-03f, 4.323750E-03f, 4.006709E-03f, 3.713708E-03f, 3.443294E-03f,
    3.194041E-03f, 2.964424E-03f, 2.752492E-03f, 2.556406E-03f, 2.374564E-03f,
    2.205568E-03f, 2.048294E-03f, 1.902113E-03f, 1.766485E-03f, 1.640857E-03f,
    1.524672E-03f, 1.417322E-03f, 1.318031E-03f, 1.226059E-03f, 1.140743E-03f,
    1.061495E-03f, 9.877949E-04f, 9.191847E-04f, 8.552568E-04f, 7.956433E-04f,
    7.400120E-04f, 6.880980E-04f, 6.397864E-04f, 5.949726E-04f, 5.535291E-04f,
    5.153113E-04f, 4.801234E-04f, 4.476245E-04f, 4.174846E-04f, 3.894221E-04f,
    3.631969E-04f, 3.386279E-04f, 3.156452E-04f, 2.941966E-04f, 2.742235E-04f,
    2.556624E-04f, 2.384390E-04f, 2.224525E-04f, 2.076036E-04f, 1.938018E-04f,
    1.809649E-04f, 1.690167E-04f, 1.578839E-04f, 1.474993E-04f, 1.378026E-04f,
    1.287394E-04f, 1.202644E-04f, 1.123502E-04f, 1.049725E-04f, 9.810596E-05f,
    9.172477E-05f, 8.579861E-05f, 8.028174E-05f, 7.513013E-05f, 7.030565E-05f,
    6.577532E-05f, 6.151508E-05f, 5.752025E-05f, 5.378813E-05f, 5.031350E-05f,
    4.708916E-05f, 4.410322E-05f, 4.133150E-05f, 3.874992E-05f, 3.633762E-05f,
    3.407653E-05f, 3.195242E-05f, 2.995808E-05f, 2.808781E-05f, 2.633581E-05f,
    2.469630E-05f, 2.316311E-05f, 2.172855E-05f, 2.038519E-05f, 1.912625E-05f,
    1.794555E-05f, 1.683776E-05f, 1.579907E-05f, 1.482604E-05f, 1.391527E-05f,
    1.306345E-05f, 1.226720E-05f, 1.152279E-05f, 1.082663E-05f, 1.017540E-05f,
    9.565993E-06f, 8.995405E-06f, 8.460253E-06f, 7.957382E-06f, 7.483997E-06f,
    7.037621E-06f, 6.616311E-06f, 6.219265E-06f, 5.845844E-06f, 5.495311E-06f,
    5.166853E-06f, 4.859511E-06f, 4.571973E-06f, 4.302920E-06f, 4.051121E-06f,
    3.815429E-06f, 3.594719E-06f, 3.387736E-06f, 3.193301E-06f, 3.010363E-06f,
    2.837980E-06f, 2.675365E-06f, 2.522020E-06f, 2.377511E-06f, 2.241417E-06f,
    2.113325E-06f, 1.992830E-06f, 1.879542E-06f, 1.773083E-06f, 1.673086E-06f,
    1.579199E-06f};

static float y_bar[] = {
    4.076779E-04f, 4.977769E-04f, 6.064754E-04f, 7.370040E-04f, 8.929388E-04f,
    1.078166E-03f, 1.296816E-03f, 1.553159E-03f, 1.851463E-03f, 2.195795E-03f,
    2.589775E-03f, 3.036799E-03f, 3.541926E-03f, 4.111422E-03f, 4.752618E-03f,
    5.474207E-03f, 6.285034E-03f, 7.188068E-03f, 8.181786E-03f, 9.260417E-03f,
    1.041303E-02f, 1.162642E-02f, 1.289884E-02f, 1.423442E-02f, 1.564080E-02f,
    1.712968E-02f, 1.871265E-02f, 2.038394E-02f, 2.212935E-02f, 2.392985E-02f,
    2.576133E-02f, 2.760156E-02f, 2.945513E-02f, 3.133884E-02f, 3.327575E-02f,
    3.529554E-02f, 3.742705E-02f, 3.967137E-02f, 4.201998E-02f, 4.446166E-02f,
    4.698226E-02f, 4.956742E-02f, 5.221219E-02f, 5.491387E-02f, 5.766919E-02f,
    6.047429E-02f, 6.332195E-02f, 6.619271E-02f, 6.906185E-02f, 7.190190E-02f,
    7.468288E-02f, 7.738452E-02f, 8.003601E-02f, 8.268524E-02f, 8.538745E-02f,
    8.820537E-02f, 9.118925E-02f, 9.431041E-02f, 9.751346E-02f, 1.007349E-01f,
    1.039030E-01f, 1.069639E-01f, 1.099676E-01f, 1.129992E-01f, 1.161541E-01f,
    1.195389E-01f, 1.232503E-01f, 1.273047E-01f, 1.316964E-01f, 1.364178E-01f,
    1.414586E-01f, 1.468003E-01f, 1.524002E-01f, 1.582021E-01f, 1.641400E-01f,
    1.701373E-01f, 1.761233E-01f, 1.820896E-01f, 1.880463E-01f, 1.940065E-01f,
    1.999859E-01f, 2.060054E-01f, 2.120981E-01f, 2.183041E-01f, 2.246686E-01f,
    2.312426E-01f, 2.380741E-01f, 2.451798E-01f, 2.525682E-01f, 2.602479E-01f,
    2.682271E-01f, 2.765005E-01f, 2.850035E-01f, 2.936475E-01f, 3.023319E-01f,
    3.109438E-01f, 3.194105E-01f, 3.278683E-01f, 3.365263E-01f, 3.456176E-01f,
    3.554018E-01f, 3.660893E-01f, 3.775857E-01f, 3.896960E-01f, 4.021947E-01f,
    4.148227E-01f, 4.273539E-01f, 4.398206E-01f, 4.523360E-01f, 4.650298E-01f,
    4.780482E-01f, 4.915173E-01f, 5.054224E-01f, 5.197057E-01f, 5.343012E-01f,
    5.491344E-01f, 5.641302E-01f, 5.792416E-01f, 5.944264E-01f, 6.096388E-01f,
    6.248296E-01f, 6.399656E-01f, 6.550943E-01f, 6.702903E-01f, 6.856375E-01f,
    7.012292E-01f, 7.171103E-01f, 7.330917E-01f, 7.489041E-01f, 7.642530E-01f,
    7.788199E-01f, 7.923410E-01f, 8.048510E-01f, 8.164747E-01f, 8.273520E-01f,
    8.376358E-01f, 8.474653E-01f, 8.568868E-01f, 8.659242E-01f, 8.746041E-01f,
    8.829552E-01f, 8.910274E-01f, 8.989495E-01f, 9.068753E-01f, 9.149652E-01f,
    9.233858E-01f, 9.322325E-01f, 9.412862E-01f, 9.502378E-01f, 9.587647E-01f,
    9.665325E-01f, 9.732504E-01f, 9.788415E-01f, 9.832867E-01f, 9.865720E-01f,
    9.886887E-01f, 9.897056E-01f, 9.899849E-01f, 9.899624E-01f, 9.900731E-01f,
    9.907500E-01f, 9.922826E-01f, 9.943837E-01f, 9.966221E-01f, 9.985649E-01f,
    9.997775E-01f, 9.999440E-01f, 9.992200E-01f, 9.978793E-01f, 9.961934E-01f,
    9.944304E-01f, 9.927831E-01f, 9.911578E-01f, 9.893925E-01f, 9.873288E-01f,
    9.848127E-01f, 9.817253E-01f, 9.780714E-01f, 9.738860E-01f, 9.692028E-01f,
    9.640545E-01f, 9.584409E-01f, 9.522379E-01f, 9.452968E-01f, 9.374773E-01f,
    9.286495E-01f, 9.187953E-01f, 9.083014E-01f, 8.976352E-01f, 8.872401E-01f,
    8.775360E-01f, 8.687920E-01f, 8.607474E-01f, 8.530233E-01f, 8.452535E-01f,
    8.370838E-01f, 8.282409E-01f, 8.187320E-01f, 8.086352E-01f, 7.980296E-01f,
    7.869950E-01f, 7.756040E-01f, 7.638996E-01f, 7.519157E-01f, 7.396832E-01f,
    7.272309E-01f, 7.145878E-01f, 7.017926E-01f, 6.888866E-01f, 6.759103E-01f,
    6.629035E-01f, 6.498911E-01f, 6.368410E-01f, 6.237092E-01f, 6.104541E-01f,
    5.970375E-01f, 5.834395E-01f, 5.697044E-01f, 5.558892E-01f, 5.420475E-01f,
    5.282296E-01f, 5.144746E-01f, 5.007881E-01f, 4.871687E-01f, 4.736160E-01f,
    4.601308E-01f, 4.467260E-01f, 4.334589E-01f, 4.203919E-01f, 4.075810E-01f,
    3.950755E-01f, 3.828894E-01f, 3.709190E-01f, 3.590447E-01f, 3.471615E-01f,
    3.351794E-01f, 3.230562E-01f, 3.108859E-01f, 2.987840E-01f, 2.868527E-01f,
    2.751807E-01f, 2.638343E-01f, 2.528330E-01f, 2.421835E-01f, 2.318904E-01f,
    2.219564E-01f, 2.123826E-01f, 2.031698E-01f, 1.943179E-01f, 1.858250E-01f,
    1.776882E-01f, 1.698926E-01f, 1.623822E-01f, 1.550986E-01f, 1.479918E-01f,
    1.410203E-01f, 1.341614E-01f, 1.274401E-01f, 1.208887E-01f, 1.145345E-01f,
    1.083996E-01f, 1.025007E-01f, 9.684588E-02f, 9.143944E-02f, 8.628318E-02f,
    8.137687E-02f, 7.671708E-02f, 7.229404E-02f, 6.809696E-02f, 6.411549E-02f,
    6.033976E-02f, 5.676054E-02f, 5.336992E-02f, 5.016027E-02f, 4.712405E-02f,
    4.425383E-02f, 4.154205E-02f, 3.898042E-02f, 3.656091E-02f, 3.427597E-02f,
    3.211852E-02f, 3.008192E-02f, 2.816001E-02f, 2.634698E-02f, 2.463731E-02f,
    2.302574E-02f, 2.150743E-02f, 2.007838E-02f, 1.873474E-02f, 1.747269E-02f,
    1.628841E-02f, 1.517767E-02f, 1.413473E-02f, 1.315408E-02f, 1.223092E-02f,
    1.136106E-02f, 1.054190E-02f, 9.775050E-03f, 9.061962E-03f, 8.402962E-03f,
    7.797457E-03f, 7.243230E-03f, 6.734381E-03f, 6.265001E-03f, 5.830085E-03f,
    5.425391E-03f, 5.047634E-03f, 4.695140E-03f, 4.366592E-03f, 4.060685E-03f,
    3.776140E-03f, 3.511578E-03f, 3.265211E-03f, 3.035344E-03f, 2.820496E-03f,
    2.619372E-03f, 2.430960E-03f, 2.254796E-03f, 2.090489E-03f, 1.937586E-03f,
    1.795595E-03f, 1.663989E-03f, 1.542195E-03f, 1.429639E-03f, 1.325752E-03f,
    1.229980E-03f, 1.141734E-03f, 1.060269E-03f, 9.848854E-04f, 9.149703E-04f,
    8.499903E-04f, 7.895158E-04f, 7.333038E-04f, 6.811458E-04f, 6.328287E-04f,
    5.881375E-04f, 5.468389E-04f, 5.086349E-04f, 4.732403E-04f, 4.404016E-04f,
    4.098928E-04f, 3.815137E-04f, 3.550902E-04f, 3.304668E-04f, 3.075030E-04f,
    2.860718E-04f, 2.660718E-04f, 2.474586E-04f, 2.301919E-04f, 2.142225E-04f,
    1.994949E-04f, 1.859336E-04f, 1.734067E-04f, 1.617865E-04f, 1.509641E-04f,
    1.408466E-04f, 1.313642E-04f, 1.224905E-04f, 1.142060E-04f, 1.064886E-04f,
    9.931439E-05f, 9.265512E-05f, 8.647225E-05f, 8.072780E-05f, 7.538716E-05f,
    7.041878E-05f, 6.579338E-05f, 6.148250E-05f, 5.746008E-05f, 5.370272E-05f,
    5.018934E-05f, 4.690245E-05f, 4.383167E-05f, 4.096780E-05f, 3.830123E-05f,
    3.582218E-05f, 3.351903E-05f, 3.137419E-05f, 2.937068E-05f, 2.749380E-05f,
    2.573083E-05f, 2.407249E-05f, 2.251704E-05f, 2.106350E-05f, 1.970991E-05f,
    1.845353E-05f, 1.728979E-05f, 1.620928E-05f, 1.520262E-05f, 1.426169E-05f,
    1.337946E-05f, 1.255038E-05f, 1.177169E-05f, 1.104118E-05f, 1.035662E-05f,
    9.715798E-06f, 9.116316E-06f, 8.555201E-06f, 8.029561E-06f, 7.536768E-06f,
    7.074424E-06f, 6.640464E-06f, 6.233437E-06f, 5.852035E-06f, 5.494963E-06f,
    5.160948E-06f, 4.848687E-06f, 4.556705E-06f, 4.283580E-06f, 4.027993E-06f,
    3.788729E-06f, 3.564599E-06f, 3.354285E-06f, 3.156557E-06f, 2.970326E-06f,
    2.794625E-06f, 2.628701E-06f, 2.472248E-06f, 2.325030E-06f, 2.186768E-06f,
    2.057152E-06f, 1.935813E-06f, 1.822239E-06f, 1.715914E-06f, 1.616355E-06f,
    1.523114E-06f, 1.435750E-06f, 1.353771E-06f, 1.276714E-06f, 1.204166E-06f,
    1.135758E-06f, 1.071181E-06f, 1.010243E-06f, 9.527779E-07f, 8.986224E-07f,
    8.476168E-07f, 7.996052E-07f, 7.544361E-07f, 7.119624E-07f, 6.720421E-07f,
    6.345380E-07f};

static float z_bar[] = {
    1.318752E-02f, 1.597879E-02f, 1.935758E-02f, 2.343758E-02f, 2.835021E-02f,
    3.424588E-02f, 4.129467E-02f, 4.968641E-02f, 5.962964E-02f, 7.134926E-02f,
    8.508254E-02f, 1.010753E-01f, 1.195838E-01f, 1.408647E-01f, 1.651644E-01f,
    1.927065E-01f, 2.236782E-01f, 2.582109E-01f, 2.963632E-01f, 3.381018E-01f,
    3.832822E-01f, 4.316884E-01f, 4.832440E-01f, 5.379345E-01f, 5.957740E-01f,
    6.568187E-01f, 7.210459E-01f, 7.878635E-01f, 8.563391E-01f, 9.253017E-01f,
    9.933444E-01f, 1.059178E+00f, 1.122832E+00f, 1.184947E+00f, 1.246476E+00f,
    1.308674E+00f, 1.372628E+00f, 1.437661E+00f, 1.502449E+00f, 1.565456E+00f,
    1.624940E+00f, 1.679488E+00f, 1.729668E+00f, 1.776755E+00f, 1.822228E+00f,
    1.867751E+00f, 1.914504E+00f, 1.961055E+00f, 2.005136E+00f, 2.044296E+00f,
    2.075946E+00f, 2.098231E+00f, 2.112591E+00f, 2.121427E+00f, 2.127239E+00f,
    2.132574E+00f, 2.139093E+00f, 2.144815E+00f, 2.146832E+00f, 2.142250E+00f,
    2.128264E+00f, 2.103205E+00f, 2.069388E+00f, 2.030030E+00f, 1.988178E+00f,
    1.946651E+00f, 1.907521E+00f, 1.870689E+00f, 1.835578E+00f, 1.801657E+00f,
    1.768440E+00f, 1.735338E+00f, 1.701254E+00f, 1.665053E+00f, 1.625712E+00f,
    1.582342E+00f, 1.534439E+00f, 1.482544E+00f, 1.427438E+00f, 1.369876E+00f,
    1.310576E+00f, 1.250226E+00f, 1.189511E+00f, 1.129050E+00f, 1.069379E+00f,
    1.010952E+00f, 9.541809E-01f, 8.995253E-01f, 8.473720E-01f, 7.980093E-01f,
    7.516389E-01f, 7.082645E-01f, 6.673867E-01f, 6.284798E-01f, 5.911174E-01f,
    5.549619E-01f, 5.198843E-01f, 4.862772E-01f, 4.545497E-01f, 4.249955E-01f,
    3.978114E-01f, 3.730218E-01f, 3.502618E-01f, 3.291407E-01f, 3.093356E-01f,
    2.905816E-01f, 2.726773E-01f, 2.555143E-01f, 2.390188E-01f, 2.231335E-01f,
    2.078158E-01f, 1.930407E-01f, 1.788089E-01f, 1.651287E-01f, 1.520103E-01f,
    1.394643E-01f, 1.275353E-01f, 1.163771E-01f, 1.061161E-01f, 9.682266E-02f,
    8.852389E-02f, 8.118263E-02f, 7.463132E-02f, 6.870644E-02f, 6.327834E-02f,
    5.824484E-02f, 5.353812E-02f, 4.914863E-02f, 4.507511E-02f, 4.131175E-02f,
    3.784916E-02f, 3.467234E-02f, 3.175471E-02f, 2.907029E-02f, 2.659651E-02f,
    2.431375E-02f, 2.220677E-02f, 2.026852E-02f, 1.849246E-02f, 1.687084E-02f,
    1.539505E-02f, 1.405450E-02f, 1.283354E-02f, 1.171754E-02f, 1.069415E-02f,
    9.753000E-03f, 8.886096E-03f, 8.089323E-03f, 7.359131E-03f, 6.691736E-03f,
    6.083223E-03f, 5.529423E-03f, 5.025504E-03f, 4.566879E-03f, 4.149405E-03f,
    3.769336E-03f, 3.423302E-03f, 3.108313E-03f, 2.821650E-03f, 2.560830E-03f,
    2.323578E-03f, 2.107847E-03f, 1.911867E-03f, 1.734006E-03f, 1.572736E-03f,
    1.426627E-03f, 1.294325E-03f, 1.174475E-03f, 1.065842E-03f, 9.673215E-04f,
    8.779264E-04f, 7.967847E-04f, 7.231502E-04f, 6.563501E-04f, 5.957678E-04f,
    5.408385E-04f, 4.910441E-04f, 4.459046E-04f, 4.049826E-04f, 3.678818E-04f,
    3.342429E-04f, 3.037407E-04f, 2.760809E-04f, 2.509970E-04f, 2.282474E-04f,
    2.076129E-04f, 1.888948E-04f, 1.719127E-04f, 1.565030E-04f, 1.425177E-04f,
    1.298230E-04f, 1.182974E-04f, 1.078310E-04f, 9.832455E-05f, 8.968787E-05f,
    8.183954E-05f, 7.470582E-05f, 6.821991E-05f, 6.232132E-05f, 5.695534E-05f,
    5.207245E-05f, 4.762781E-05f, 4.358082E-05f, 3.989468E-05f, 3.653612E-05f,
    3.347499E-05f, 3.068400E-05f, 2.813839E-05f, 2.581574E-05f, 2.369574E-05f,
    2.175998E-05f, 1.999179E-05f, 1.837603E-05f, 1.689896E-05f, 1.554815E-05f,
    1.431231E-05f, 1.318119E-05f, 1.214548E-05f, 1.119673E-05f, 1.032727E-05f,
    9.530130E-06f, 8.798979E-06f, 8.128065E-06f, 7.512160E-06f, 6.946506E-06f,
    6.426776E-06f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f, 0.000000E+00f,
    0.000000E+00f};


// Use http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
forma::vec3 forma::spectral_to_xyz(const std::vector<float>& values,
                                   const std::size_t& start,
                                   const std::size_t& end) {
  float delta = values.size() / static_cast<float>(end - start);
  vec3 res;
  for (std::size_t i = 0; i < values.size(); ++i) {
    res.x +=
        x_bar[static_cast<std::size_t>(delta * i) + start] * values[i] * delta;
    res.y +=
        y_bar[static_cast<std::size_t>(delta * i) + start] * values[i] * delta;
    res.z +=
        z_bar[static_cast<std::size_t>(delta * i) + start] * values[i] * delta;
  }
  return res;
}
forma::vec3 forma::spectral_to_lab(const std::vector<float>& values,
                                   const std::size_t& start,
                                   const std::size_t& end) {
  return xyz_to_lab(spectral_to_xyz(values, start, end));
}
forma::vec3 forma::spectral_to_rgb(const std::vector<float>& values,
                                   const std::size_t& start,
                                   const std::size_t& end) {
  return xyz_to_rgb(spectral_to_xyz(values, start, end));
}
forma::vec3 forma::spectral_to_hsv(const std::vector<float>& values,
                                   const std::size_t& start,
                                   const std::size_t& end) {
  return rgb_to_hsv(xyz_to_rgb(spectral_to_xyz(values, start, end)));
}
forma::vec3 forma::spectral_to_hsl(const std::vector<float>& values,
                                   const std::size_t& start,
                                   const std::size_t& end) {
  return rgb_to_hsl(xyz_to_rgb(spectral_to_xyz(values, start, end)));
}

forma::vec3 forma::xyz_to_lab(const float& x, const float& y, const float& z) {
  float xr = x / d65[0];
  float yr = y / d65[1];
  float zr = z / d65[2];
  float fx =
      (xr > CIE_EPSILON) ? std::cbrt(xr) : (CIE_KAPPA * xr + 16.0f) / 116.0f;
  float fy =
      (yr > CIE_EPSILON) ? std::cbrt(yr) : (CIE_KAPPA * yr + 16.0f) / 116.0f;
  float fz =
      (zr > CIE_EPSILON) ? std::cbrt(zr) : (CIE_KAPPA * zr + 16.0f) / 116.0f;
  return {116.0f * fy - 16.0f, 500.0f * (fx - fy), 200.0f * (fy - fz)};
}
forma::vec3 forma::xyz_to_rgb(const float& x, const float& y, const float& z) {
  return {
      3.2404542 * x - 1.5371385 * y - 0.4985314 * z,
      -0.9692660 * x + 1.8760108 * y + 0.0415560 * z,
      0.0556434 * x - 0.2040259 * y + 1.0572252 * z,
  };
}
forma::vec3 forma::xyz_to_hsv(const float& x, const float& y, const float& z) {
  return rgb_to_hsv(xyz_to_rgb(x, y, z));
}
forma::vec3 forma::xyz_to_hsl(const float& x, const float& y, const float& z) {
  return rgb_to_hsl(xyz_to_rgb(x, y, z));
}
forma::vec3 forma::lab_to_xyz(const float& l, const float& a, const float& b) {
  float fy = (l + 16.0f) / 116.0f;
  float fx = a / 500.0f + fy;
  float fz = fy - b / 200.0f;
  float xr = (fx * fx * fx > CIE_EPSILON) ? fx * fx * fx
                                          : (116.0f * fx - 16) / CIE_KAPPA;
  float yr = (l > CIE_KAPPA * CIE_EPSILON) ? std::pow((l + 16.0f) / 116.0f, 3)
                                           : l / CIE_KAPPA;
  float zr = (fz * fz * fz > CIE_EPSILON) ? fz * fz * fz
                                          : (116.0f * fz - 16) / CIE_KAPPA;
  return {xr * d65[0], yr * d65[1], zr * d65[2]};
}
forma::vec3 forma::lab_to_rgb(const float& l, const float& a, const float& b) {
  return xyz_to_rgb(lab_to_xyz(l, a, b));
}
forma::vec3 forma::lab_to_hsv(const float& l, const float& a, const float& b) {
  return rgb_to_hsv(xyz_to_rgb(lab_to_xyz(l, a, b)));
}
forma::vec3 forma::lab_to_hsl(const float& l, const float& a, const float& b) {
  return rgb_to_hsl(xyz_to_rgb(lab_to_xyz(l, a, b)));
}
forma::vec3 forma::rgb_to_xyz(const float& r, const float& g, const float& b) {
  return {
      0.4124564 * r + 0.3575761 * g + 0.1804375 * b,
      0.2126729 * r + 0.7151522 * g + 0.0721750 * b,
      0.0193339 * r + 0.1191920 * g + 0.9503041 * b,
  };
}
forma::vec3 forma::rgb_to_lab(const float& r, const float& g, const float& b) {
  return xyz_to_lab(rgb_to_xyz(r, g, b));
}
forma::vec3 forma::rgb_to_hsv(const float& r, const float& g, const float& b) {
  float min_v = min(r, min(g, b));
  float max_v = max(r, max(g, b));
  float delta = max_v - min_v;
  float s = 0.0f;
  if (max_v != 0) {
    s = delta / max_v;
  }
  float h = 0.0f;
  if (delta == 0.0f) {
    h = 0.0f;
  } else if (max_v == r) {
    h = 60.0f * fmod((g - b) / delta, 6.0f);
  } else if (max_v == g) {
    h = 60.0f * ((b - r) / delta + 2.0f);
  } else if (max_v == b) {
    h = 60.0f * ((r - g) / delta + 4.0f);
  }
  if (h < 0) h += 360.0f;
  return {h, s, max_v};
}
forma::vec3 forma::rgb_to_hsl(const float& r, const float& g, const float& b) {
  double c_max = fmax(r, fmax(g, b));
  double c_min = fmin(r, fmin(g, b));
  double delta = c_max - c_min;
  double h = 0, s = 0, l = 0;
  if (delta == 0) {
    h = 0;
  } else if (c_max == r) {
    h = 60 * fmod((g - b) / delta, 6.0);
  } else if (c_max == g) {
    h = 60 * ((b - r) / delta + 2);
  } else if (c_max == b) {
    h = 60 * ((r - g) / delta + 4);
  }
  if (h < 0) {
    h += 360.0;
  }
  l = (c_max + c_min) / 2;
  if (c_max == 0) {
    s = 0;
  } else {
    s = delta / (1.0 - fabs(2 * l - 1.0));
  }
  return {h, s, l};
}
forma::vec3 forma::hsv_to_xyz(const float& h, const float& s, const float& v) {
  return rgb_to_xyz(hsv_to_rgb(h, s, v));
}
forma::vec3 forma::hsv_to_lab(const float& h, const float& s, const float& v) {
  return xyz_to_lab(rgb_to_xyz(hsv_to_rgb(h, s, v)));
}
forma::vec3 forma::hsv_to_rgb(const float& h, const float& s, const float& v) {
  float c = v * s;
  float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
  float m = v - c;
  if (h < 60.0) {
    return {c + m, x + m, m};
  } else if (h < 120.0) {
    return {x + m, c + m, m};
  } else if (h < 180.0) {
    return {m, c + m, x + m};
  } else if (h < 240.0) {
    return {m, x + m, c + m};
  } else if (h < 300.0) {
    return {x + m, m, c + m};
  } else {
    return {c + m, m, x + m};
  }
}
forma::vec3 forma::hsv_to_hsl(const float& h, const float& s, const float& v) {
  return rgb_to_hsl(hsv_to_rgb(h, s, v));
}
forma::vec3 forma::hsl_to_xyz(const float& h, const float& s, const float& l) {
  return rgb_to_xyz(hsl_to_rgb(h, s, l));
}
forma::vec3 forma::hsl_to_lab(const float& h, const float& s, const float& l) {
  return xyz_to_lab(rgb_to_xyz(hsl_to_rgb(h, s, l)));
}
forma::vec3 forma::hsl_to_rgb(const float& h, const float& s, const float& l) {
  double c = (1.0 - fabs(2 * l - 1.0)) * s;
  double x = c * (1.0 - fabs(fmod(h / 60.0, 2.0) - 1.0));
  double m = l - c / 2.0;
  if (h < 60.0) {
    return {c + m, x + m, m};
  } else if (h < 120.0) {
    return {x + m, c + m, m};
  } else if (h < 180.0) {
    return {m, c + m, x + m};
  } else if (h < 240.0) {
    return {m, x + m, c + m};
  } else if (h < 300.0) {
    return {x + m, m, c + m};
  } else {
    return {c + m, m, x + m};
  }
}
forma::vec3 forma::hsl_to_hsv(const float& h, const float& s, const float& l) {
  return rgb_to_hsv(hsl_to_rgb(h, s, l));
}
