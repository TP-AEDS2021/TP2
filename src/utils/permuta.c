int nextPerm(int perm[], int k, int n)
{
  bool invalid = true;
  int subject, i;
  if (k == 1)
  {
    if (perm[0] == n - 1)
      return 0;
    else
    {
      perm[0] = perm[0] + 1;
      return 1;
    }
  }
  subject = perm[k - 1] + 1;
  while (invalid)
  {
    if (subject == n)
    {
      subject = 0;
      if (!nextPerm(perm, k - 1, n))
        return 0;
    }
    for (i = 0; i < k - 1; i++)
    {
      if (perm[i] != subject)
        invalid = false;
      else
      {
        invalid = true;
        subject++;
        break;
      }
    }
  }
  perm[k - 1] = subject;
  return 1;
}