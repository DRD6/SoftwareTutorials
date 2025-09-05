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
