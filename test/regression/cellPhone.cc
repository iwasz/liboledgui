/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "cellPhone.h"
#include "regression.h"

namespace {
using namespace og;
using namespace std::string_view_literals;

enum class Win { desktop, dropDown };
ISuite<Win> *mySuite{};

int volumeLevel{1};

auto volume = hbox<2> (combo<CanFocus::no> (std::ref (volumeLevel), option (0, "🕨"sv), option (1, "🕩"sv), option (2, "🕪"sv)));

auto desktop = window<0, 0, 18, 7> (vbox (
        hbox (label ("12:34"sv), hspace<10>, std::ref (volume), button ("…"sv, [] { mySuite->current () = Win::dropDown; })), // top status bar
        hbox ()

                ));

/*--------------------------------------------------------------------------*/

auto dropDown = window<10, 1, 8, 6, true> (
        vbox (label ("menu"sv),                                                                        // title
              combo (std::ref (volumeLevel), option (0, "0"sv), option (1, "1"sv), option (2, "2"sv)), // volume option (settable)
              button ("close"sv, [] { mySuite->current () = Win::desktop; }),                          //
              button ("shut-dn"sv, [] { mainMenu (); })));

auto cellP = suite (element (Win::desktop, std::ref (desktop)),                      // Desktop only
                    element (Win::dropDown, std::ref (desktop), std::ref (dropDown)) // Desktop covered by the menu

);

} // namespace

og::detail::augment::IWindow &cellPhone ()
{
        mySuite = &cellP;
        return cellP;
}