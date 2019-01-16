function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33293, y = 32741, z = 13},3042) then 
		doRelocate({x = 33293, y = 32742, z = 13},{x = 33299, y = 32742, z = 13})
		Game.sendMagicEffect({x = 33293, y = 32742, z = 13}, 11)
		Game.sendMagicEffect({x = 33299, y = 32742, z = 13}, 11)
		Game.sendMagicEffect({x = 33293, y = 32741, z = 13}, 16)
		Game.removeItemOnMap({x = 33293, y = 32741, z = 13}, 3042)
	else 
		Game.sendMagicEffect({x = 33293, y = 32741, z = 13}, 3)
	end
end
