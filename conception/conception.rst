Conception du projet
====================


Analyseur syntaxique
--------------------

- Il connaît l'ensemble des règles de syntaxe. Il sait donc de quel mot clé à
  quel autre mot clé demander une lecture à l'analyseur lexical.

- Il demande à l'analyseur lexical de lui fournir les tokens analysés.

Analyseur lexical
-----------------

- Lors d'une demande de l'analyseur syntaxique, analyse chacun des tokens de
  façon à ce que ceux-ci soient valides avant d'êtres passés (les tokens doivent
  faire parti du lexique).
