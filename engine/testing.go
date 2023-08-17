package engine

func RunEngine() {
	run_uci()
}

func run_uci() {
	uci_engine := &UCIEngine{}
	uci_engine.UCILoop()
}
