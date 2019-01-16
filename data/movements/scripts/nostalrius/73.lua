function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32800, y = 31605, z = 07})
	Game.sendMagicEffect({x = 32800, y = 31605, z = 07}, 13)
	Game.sendMagicEffect({x = 32701, y = 31638, z = 06}, 11)
end
