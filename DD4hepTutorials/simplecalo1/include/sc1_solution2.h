/*
 * Copyright (c) 2020-2024 Key4hep-Project.
 *
 * This file is part of Key4hep.
 * See https://key4hep.github.io/key4hep-doc/ for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Place an absorber layer inside the calorimeter layer
//
Box AbsLayer(AbsLayerX / 2., AbsLayerY / 2., AbsLayerZ / 2.);
Volume AbsLayerVol(
    "AbsLayerVol", AbsLayer,
    description.material(x_abslayer.attr<std::string>(_U(material))));
AbsLayerVol.setVisAttributes(description, x_abslayer.visStr());
PlacedVolume AbsLayerPlaced = CaloLayerVol.placeVolume(
    AbsLayerVol, 1, Position(0., 0., -CaloLayerZ / 2. + AbsLayerZ / 2.));
AbsLayerPlaced.addPhysVolID("abslayer", 1);

// Place an active layer inside the calorimeter layer
//
Box SensLayer(SensLayerX / 2., SensLayerY / 2., SensLayerZ / 2.);
Volume SensLayerVol(
    "SensLayerVol", SensLayer,
    description.material(x_senslayer.attr<std::string>(_U(material))));
SensLayerVol.setVisAttributes(description, x_senslayer.visStr());
PlacedVolume SensLayerPlaced = CaloLayerVol.placeVolume(
    SensLayerVol, 1, Position(0., 0., CaloLayerZ / 2. - SensLayerZ / 2.));
SensLayerPlaced.addPhysVolID("abslayer", 0);
