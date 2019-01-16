function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33073, y = 32589, z = 13},3042) then 
		doRelocate({x = 33073, y = 32590, z = 13},{x = 33080, y = 32588, z = 13})
		Game.sendMagicEffect({x = 33073, y = 32590, z = 13}, 11)
		Game.sendMagicEffect({x = 33080, y = 32589, z = 13}, 11)
		Game.sendMagicEffect({x = 33073, y = 32589, z = 13}, 16)
		Game.removeItemOnMap({x = 33073, y = 32589, z = 13}, 3042)
	else
		Game.sendMagicEffect({x = 33073, y = 32589, z = 13}, 3)
	end
end
