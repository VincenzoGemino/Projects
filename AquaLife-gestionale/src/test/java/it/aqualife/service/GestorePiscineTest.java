package test.java.it.aqualife.service;
import java.time.LocalDateTime;
import java.time.YearMonth;
import java.time.Duration;
import java.util.*;
import java.util.stream.Collectors;

import main.java.it.aqualife.service.GestoreAquaLife;

public class GestorePiscineTest {
    public static void main(String[] args) {
        System.out.println("--- AVVIO TEST GESTIONALE AQUALIFE ---");
        GestoreAquaLife gestore = new GestoreAquaLife();

        // 1. Setup Dati
        Stabilimento s1 = new Stabilimento("S1", "AquaLife Centro", "Via Roma 1");
        Piscina p1 = new Piscina("P1", "Olimpionica", s1);
        Piscina p2 = new Piscina("P2", "Bambini", s1);

        Lavoratore istruttore1 = new Lavoratore("L1", "Mario Rossi", RuoloLavoratore.ISTRUTTORE);
        Lavoratore istruttore2 = new Lavoratore("L2", "Luigi Verdi", RuoloLavoratore.ISTRUTTORE);

        Cliente c1 = new Cliente("C1", "Studente Uno", TipoCliente.UNIVERSITARIO);
        Cliente c2 = new Cliente("C2", "Studente Due", TipoCliente.UNIVERSITARIO);
        Cliente c3 = new Cliente("C3", "Famiglia Bianchi", TipoCliente.GRUPPO);

        Corso corsoNuoto = new Corso("CR1", "Nuoto Avanzato", p1, istruttore1, 50.0);
        Corso corsoAcquaGym = new Corso("CR2", "AcquaGym", p2, istruttore2, 30.0);

        gestore.addPiscina(p1); gestore.addPiscina(p2);
        gestore.addLavoratore(istruttore1); gestore.addLavoratore(istruttore2);
        gestore.addCliente(c1); gestore.addCliente(c2); gestore.addCliente(c3);
        gestore.addCorso(corsoNuoto); gestore.addCorso(corsoAcquaGym);

        LocalDateTime oraInizio = LocalDateTime.of(2023, 10, 20, 10, 0);
        LocalDateTime oraFine = LocalDateTime.of(2023, 10, 20, 11, 0);

        // 2. Test Manutenzione ed Eccezioni (Blocco 3)
        gestore.addManutenzione(new Manutenzione("M1", p1, oraInizio.minusHours(1), oraInizio.plusMinutes(30), "Pulizia filtri"));

        System.out.println("\nTest 1: Verifica Eccezione Manutenzione");
        Prenotazione prenErrore = new Prenotazione("PR_ERR", c1, corsoNuoto, oraInizio, oraFine);
        try {
            gestore.aggiungiPrenotazione(prenErrore);
            System.err.println("FALLITO: Eccezione non lanciata!");
        } catch (PrenotazioneException e) {
            System.out.println("SUPERATO: " + e.getMessage());
        }

        // Aggiungiamo prenotazioni valide
        try {
            LocalDateTime orarioValidoInizio = LocalDateTime.of(2023, 10, 21, 15, 0);
            LocalDateTime orarioValidoFine = LocalDateTime.of(2023, 10, 21, 16, 0);
            gestore.aggiungiPrenotazione(new Prenotazione("PR1", c1, corsoNuoto, orarioValidoInizio, orarioValidoFine));
            gestore.aggiungiPrenotazione(new Prenotazione("PR2", c2, corsoNuoto, orarioValidoInizio, orarioValidoFine)); // Stesso corso e orario ok
            gestore.aggiungiPrenotazione(new Prenotazione("PR3", c3, corsoAcquaGym, orarioValidoInizio, orarioValidoFine));
            System.out.println("SUPERATO: Prenotazioni valide aggiunte correttamente.");
        } catch (Exception e) {
            System.err.println("FALLITO: Errore inatteso - " + e.getMessage());
        }

        // 3. Test Stream API (Blocco 4)
        System.out.println("\nTest 2: Conteggio Tipologia Clienti");
        Map<TipoCliente, Long> conteggio = gestore.contaClientiPerTipologia();
        if (conteggio.get(TipoCliente.UNIVERSITARIO) == 2 && conteggio.get(TipoCliente.GRUPPO) == 1) {
            System.out.println("SUPERATO.");
        } else {
            System.err.println("FALLITO. Risultato: " + conteggio);
        }

        System.out.println("\nTest 3: Introiti per Istruttore");
        Map<Lavoratore, Double> introiti = gestore.calcolaIntroitiPerIstruttore(YearMonth.of(2023, 10));
        // Mario Rossi (L1) ha 2 prenotazioni a 50.0 = 100.0
        // Luigi Verdi (L2) ha 1 prenotazione a 30.0 = 30.0
        if (introiti.get(istruttore1) == 100.0 && introiti.get(istruttore2) == 30.0) {
            System.out.println("SUPERATO. (Mario: 100.0, Luigi: 30.0)");
        } else {
            System.err.println("FALLITO. Risultato: " + introiti);
        }

        System.out.println("\nTest 4: Piscina più problematica");
        gestore.addManutenzione(new Manutenzione("M2", p1, oraInizio.plusDays(1), oraInizio.plusDays(1).plusHours(5), "Guasto tubi")); // + 5 ore a P1
        Optional<Piscina> peggiore = gestore.piscinaPiuProblematiche(s1);
        if (peggiore.isPresent() && peggiore.get().id().equals("P1")) {
            System.out.println("SUPERATO. Piscina problematica: " + peggiore.get().nome());
        } else {
            System.err.println("FALLITO.");
        }
        System.out.println("\n--- FINE TEST ---");
    }
}