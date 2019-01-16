function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33098, y = 32816, z = 13},3042) then
		doRelocate({x = 33097, y = 32816, z = 13},{x = 33093, y = 32824, z = 13})
		Game.sendMagicEffect({x = 33097, y = 32816, z = 13}, 11)
		Game.sendMagicEffect({x = 33093, y = 32824, z = 13}, 11)
		Game.sendMagicEffect({x = 33098, y = 32816, z = 13}, 16)
		Game.removeItemOnMap({x = 33098, y = 32816, z = 13}, 3042)
	else
		Game.sendMagicEffect({x = 33098, y = 32816, z = 13}, 3)
	end
end
