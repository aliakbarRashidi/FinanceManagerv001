#Designed by Esmeald Aliaj. 2016 <greenleafone7@gmail.com>

exists(user.conf): include(user.conf)

isEmpty(FinanceManagerVersion) {
    FinanceManagerMajorVersion = 0
    FinanceManagerMinorVersion = 0
    FinanceManagerPatchVersion = 1
    FinanceManagerVersion = $${FinanceManagerMajorVersion}.$${FinanceManagerMinorVersion}.$${FinanceManagerPatchVersion}
    message("FinanceManagerVersion not set, cache the default $$FinanceManagerVersion")
    cache(FinanceManagerMajorVersion, set, FinanceManagerMajorVersion)
    cache(FinanceManagerMinorVersion, set, FinanceManagerMinorVersion)
    cache(FinanceManagerPatchVersion, set, FinanceManagerPatchVersion)
    cache(FinanceManagerVersion, set, FinanceManagerVersion)
}

WARNINGS += -Wall
