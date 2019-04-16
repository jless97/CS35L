#!/bin/sh

grep '<td>.\{1,\}</td>' |

sed '1d; n; d' | 

sed 's/<[^>]*>//g' |

sed 's/`/'\''/g' |         

tr ', ' '[\n*]' |

sed '/n$/d' |

tr '[:upper:]' '[:lower:]' |

sed '/[^p^k^'\''^m^n^w^l^h^a^e^i^o^u]/d' |

sort -u



