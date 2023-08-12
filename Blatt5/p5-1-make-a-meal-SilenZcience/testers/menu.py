from testers.target import Target

menu = Target("menu", text="Alles geschafft!")
vorspeise = Target("vorspeise", text="Vorspeise servieren...")
hauptgericht = Target("hauptgericht", text="Hauptgericht servieren...")
dessert = Target("dessert", text="Dessert servieren...")

salat_putzen = Target("salat-putzen", text="Salat putzen.")
dressing_herstellen = Target("dressing-herstellen", text="Dressing herstellen.")
kraeuter_hacken = Target("kraeuter-hacken", text="Kräuter hacken.")

kartoffeln_kochen = Target("kartoffeln-kochen", text="Kartoffeln kochen.")
kartoffeln_schneiden = Target("kartoffeln-schneiden", text="Kartoffeln schneiden.")
wasser_aufsetzen = Target("wasser-aufsetzen", text="Wasser aufsetzen.")

fleisch_zubereiten = Target("fleisch-zubereiten", text="Fleisch zubereiten.")
fleisch_braten = Target("fleisch-anbraten", text="Fleisch anbraten.")
fleisch_wuerzen = Target("fleisch-wuerzen", text="Fleisch würzen.")
fleisch_schneiden = Target("fleisch-schneiden", text="Fleisch schneiden.")

eis_portionieren = Target("eis-portionieren", text="Eis portionieren.")
gruetze_verteilen = Target("gruetze-verteilen", text="Grütze verteilen.")
mit_schoko_garnieren = Target("mit-schoko-garnieren", text="Mit Schokoladenraspeln garnieren.")

menu.depends = [vorspeise, hauptgericht, dessert]
vorspeise.depends = [salat_putzen, dressing_herstellen]
dressing_herstellen.depends = [kraeuter_hacken]

hauptgericht.depends = [vorspeise, kartoffeln_kochen, fleisch_zubereiten]
kartoffeln_kochen.depends = [kartoffeln_schneiden, wasser_aufsetzen]
fleisch_zubereiten.depends = [fleisch_braten, fleisch_wuerzen]
fleisch_braten.depends = [fleisch_schneiden]

dessert.depends = [hauptgericht, mit_schoko_garnieren]
mit_schoko_garnieren.depends = [gruetze_verteilen]
gruetze_verteilen.depends = [eis_portionieren]
