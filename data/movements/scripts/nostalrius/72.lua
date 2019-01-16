function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32775, y = 31595, z = 07})
	Game.sendMagicEffect({x = 32775, y = 31595, z = 07}, 13)
	Game.sendMagicEffect({x = 32701, y = 31637, z = 06}, 11)
end
