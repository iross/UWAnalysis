{
  NtuplePlotter *data = new NtuplePlotter("muMuEventTree/eventTree");
  data->registerFile("sandbox/zmm-latest/DATA.root");
  NtuplePlotter *mc = new NtuplePlotter("muMuEventTree/eventTree");
  mc->registerFile("sandbox/zmm-latest/MC.root");
}
