def backt(listaDrepte, index, panta, listaFinala):
	if index == k:
		#afiseaza listaFinala
	else:
		for i in listaDrepte:
			if i.getM() == panta:
				listaFinala.append(i) # pui dreapta i la lista de drepte
				backt(listaDrepte, index + 1, panta, listaFinala) # reapelezi functia cu index + 1 pentru ca vrei urmatorul element
												# adica urmatoarea dreapta paralela cu restul
				listaFinala.pop(len(listaFinala) - 1) # o stergi din lista pentru a cauta restul posibilitatilor

panteLuate = [0 for x in listaDrepte] # vector de frecventa pentru pantele dreptelor.


for i in listaDrepte:
	# iei la rand toate dreptele pentru ca poti sa ai pante diferite la drepte, si sa fie mai multe grupuri paralele
	# de ex poti sa ai lista de pante asa : 1 1 2 2 1
	# si o sa ai grupurile cu 1, si trebuie si alea cu 2, de asta ai for-ul asta
	if panteLuate[i.getM()] == 0:
		backt(listaDrepte, 0, i.getM(), []) # index = 0. cauti primul element
					# listaFinala = [], ai o lista goala la care tot o sa lipesti elemente in functia backt()
		panteLuate[i.getM()] = 1 # bifezi panta ca luata, sa nu o mai verifici dupa
