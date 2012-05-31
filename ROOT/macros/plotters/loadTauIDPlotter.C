{
  NtuplePlotter *newHPS = new NtuplePlotter("tauTree");
  newHPS->registerFile("sandbox/tauID/newHPS.root");
  NtuplePlotter *oldHPS = new NtuplePlotter("tauTree");
  oldHPS->registerFile("sandbox/tauID/oldHPS.root");

}
