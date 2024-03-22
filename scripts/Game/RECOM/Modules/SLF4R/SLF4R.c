class SLF4R : RECOM_BaseModule {
	
	private static ref SLF4R instance;
	private static LogLevel loggingLevel;
	/*
		LOGGING LEVELS
		1  = spam
	    2  = verbose
		4  = debug
		8  = normal
		16 = warning 
		32 = error
	*/
	
	static SLF4R getModule() {
        if (!SLF4R.instance) {
            SLF4R.instance = new SLF4R();
        }
        return SLF4R.instance;
    }

	private void SLF4R() {
	}

	void ~SLF4R() {
		this.loggingLevel = null;
		SLF4R.instance = null;
	}
	
	override void startModule() {
		super.startModule();
		SLF4R.loggingLevel = typename.StringToEnum(LogLevel, RECOM_PropertiesModule.getModule().getProperties().loggingLevel);
	}
	
	override void disposeModule() {
		super.disposeModule();
	}
	
	
	static void log(
		string message, 
		LogLevel level
	) {
		if (level >= SLF4R.loggingLevel) {
			Print(message, level);
		}
	}
	
	static void spam(string message) {
		log(message, LogLevel.SPAM);
	}
	
	static void verbose(string message) {
		log(message, LogLevel.VERBOSE);
	}
	
	static void debugging(string message) {
		log(message, LogLevel.DEBUG);
	}
	
	static void normal(string message) {
		log(message, LogLevel.NORMAL);
	}
	
	static void warning(string message) {
		log(message, LogLevel.WARNING);
	}
	
	static void error(string message) {
		log(message, LogLevel.ERROR);
	}
	
	static void fatal(string message) {
		log(message, LogLevel.FATAL);
	}
	
	
}
