/*
 *  Copyright © 2017-2020 Wellington Wallace
 *
 *  This file is part of PulseEffects.
 *
 *  PulseEffects is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PulseEffects is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with PulseEffects.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PULSE_SETTINGS_UI_HPP
#define PULSE_SETTINGS_UI_HPP

#include <giomm/settings.h>
#include <glibmm/i18n.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/builder.h>
#include <gtkmm/combobox.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/grid.h>
#include <gtkmm/liststore.h>
#include <gtkmm/stack.h>
#include <gtkmm/togglebutton.h>
#include "application.hpp"

class PulseSettingsUi : public Gtk::Grid {
 public:
  PulseSettingsUi(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder, Application* application);
  PulseSettingsUi(const PulseSettingsUi&) = delete;
  auto operator=(const PulseSettingsUi&) -> PulseSettingsUi& = delete;
  PulseSettingsUi(const PulseSettingsUi&&) = delete;
  auto operator=(const PulseSettingsUi &&) -> PulseSettingsUi& = delete;
  ~PulseSettingsUi() override;

  static void add_to_stack(Gtk::Stack* stack, Application* app);

 private:
  std::string log_tag = "pulse_settings_ui: ";

  Glib::RefPtr<Gio::Settings> settings, sie_settings, soe_settings;

  Application* app = nullptr;

  Gtk::ToggleButton *use_default_sink = nullptr, *use_default_source = nullptr;
  Gtk::ComboBox *input_device = nullptr, *output_device = nullptr;
  Gtk::ComboBoxText *blocksize_in = nullptr, *blocksize_out = nullptr;

  Glib::RefPtr<Gtk::Adjustment> sie_input_buffer, sie_input_latency, sie_output_buffer, sie_output_latency,
      soe_input_buffer, soe_input_latency, soe_output_buffer, soe_output_latency;

  Glib::RefPtr<Gtk::ListStore> sink_list, source_list;

  std::vector<sigc::connection> connections;

  static void get_object(const Glib::RefPtr<Gtk::Builder>& builder,
                         const std::string& name,
                         Glib::RefPtr<Gtk::Adjustment>& object) {
    object = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(builder->get_object(name));
  }

  static void get_object(const Glib::RefPtr<Gtk::Builder>& builder,
                         const std::string& name,
                         Glib::RefPtr<Gtk::ListStore>& object) {
    object = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(builder->get_object(name));
  }

  void on_sink_added(const std::shared_ptr<mySinkInfo>& info);

  void on_sink_removed(uint idx);

  void on_source_added(const std::shared_ptr<mySourceInfo>& info);

  void on_source_removed(uint idx);

  void on_use_default_sink_toggled();

  void on_use_default_source_toggled();

  void on_input_device_changed();

  void on_output_device_changed();
};

#endif
