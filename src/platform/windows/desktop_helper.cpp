#include "platform/windows/desktop_pet.h"
#include "app/desktop_helper_session.h"

namespace oa {
std::shared_ptr<DesktopHelper> CreateWindowsDesktopHelper(std::shared_ptr<AppContext> context) {
  return std::make_shared<DesktopHelperSession<DesktopPet>>(std::move(context));
}
}
