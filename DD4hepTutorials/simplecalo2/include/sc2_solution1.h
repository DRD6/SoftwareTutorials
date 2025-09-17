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
Box Cell(CellX / 2., CellY / 2., CellZ / 2.);
Volume CellVol("CellVol", Cell,
               description.material(x_cell.attr<std::string>(_U(material))));
CellVol.setVisAttributes(description, x_cell.visStr());
// Make the cell sensitive
if (iscellsens)
  CellVol.setSensitiveDetector(sens);
double x, y = 0;
for (std::size_t i = 0; i < 10; i++) {
  y = SensLayerY / 2. - CellY / 2. - i * CellY;
  for (std::size_t j = 0; j < 10; j++) {
    x = -SensLayerX / 2. + CellX / 2. + j * CellX;
    PlacedVolume CellVolPlaced =
        SensLayerVol.placeVolume(CellVol, 10 * i + j, Position(x, y, 0.));
    CellVolPlaced.addPhysVolID("cellid", 10 * i + j);
  }
}
