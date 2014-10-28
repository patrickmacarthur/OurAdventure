# Gentoo ebuild for this program (tested as of 2011-07-30)
#
# Omitting the header makes this unable to be in the portage tree but I do not
# intend to get it added anyways.

EAPI=3

# OurAdventure needs to be capitalized
MY_PN=${PN/ouradventure/OurAdventure}
MY_P=${MY_PN}-${PV}

# This needs to be done before inheriting git-2
EGIT_REPO_URI="git://github.com/patrickmacarthur/${MY_PN}.git
https://github.com/patrickmacarthur/${MY_PN}.git"

inherit games cmake-utils git-2

DESCRIPTION="Text-based adventure program originally written for UNH CS 516 final project"
HOMEPAGE="https://github.com/patrickmacarthur/OurAdventure"

LICENSE="BSD"
SLOT="0"
KEYWORDS="~x86"

IUSE=""

DEPEND=""
RDEPEND="${DEPEND}"

WANT_CMAKE="always"
CMAKE_MIN_VERSION="2.6"

DOCS="README"

S=${WORKDIR}/${MY_P}

